#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>
#include <tga2d/error/error_manager.h>

# include <imgui_node_editor.h>
# define IMGUI_DEFINE_MATH_OPERATORS
# include <imgui_internal.h>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "tga2d/d3d/direct_3d.h"

#pragma comment(lib, "imgui.lib")
#pragma comment(lib, "imgui_canvas.lib")
#pragma comment(lib, "imgui_node_editor.lib")

#include <d3d11_1.h>
#include <fstream>
#include <sstream>

#include "GraphManager.h"
#include <iostream>

#include "GameObjectManager.h"
#include "TimerManager.h"
#include "CollisionManager.h"

namespace ed = ax::NodeEditor;


GraphManager loader;
CGameWorld::CGameWorld()
{
	int count = 2;
	Tga2D::Vector2<float> pos;
	for (int i = 0; i < count; i++)
	{
		pos.x += 1.f;
		pos.y += 1.f;
		auto go = GameObjectManager::GetInstance().AddGameObject(pos);
	}
	GameObjectManager::GetInstance().SetGraphmanager(&loader);
}


CGameWorld::~CGameWorld()
{
}

static ImFont* ImGui_LoadFont(ImFontAtlas& atlas, const char* name, float size, const ImVec2& displayOffset = ImVec2(0, 0))
{
	char* windir = nullptr;
	if (_dupenv_s(&windir, nullptr, "WINDIR") || windir == nullptr)
		return nullptr;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0104, 0x017C, // Polish characters and more
		0,
	};

	ImFontConfig config;
	config.OversampleH = 4;
	config.OversampleV = 4;
	config.PixelSnapH = false;

	auto path = std::string(windir) + "\\Fonts\\" + name;
	auto font = atlas.AddFontFromFileTTF(path.c_str(), size, &config, ranges);
	if (font)
		font->DisplayOffset = displayOffset;

	free(windir);

	return font;
}
ImFontAtlas fontAtlas;
void CGameWorld::Init()
{
	ImGui_LoadFont(fontAtlas, "segoeui.ttf", 22.0f);
	fontAtlas.Build();

	ImGui::CreateContext(&fontAtlas);

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;
	io.LogFilename = nullptr;


	// Setup ImGui binding
	ImGui_ImplWin32_Init(*Tga2D::CEngine::GetInstance()->GetHWND());
	ImGui_ImplDX11_Init(Tga2D::CEngine::GetInstance()->GetDirect3D().GetDevice(), Tga2D::CEngine::GetInstance()->GetDirect3D().GetContext());

	ImGui::StyleColorsDark();
	loader.Load();
}

void CGameWorld::Update(float aTimeDelta)
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		Tga2D::CEngine::Shutdown();
	}

	TimerManager::Update();

	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX11_NewFrame();
	ImGui::NewFrame();


	loader.PreFrame(aTimeDelta);

	loader.ConstructEditorTreeAndConnectLinks();

	loader.PostFram();

	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	GameObjectManager::GetInstance().Update(aTimeDelta);
	CollisionManager::GetInstance().Update(aTimeDelta);
	GameObjectManager::GetInstance().Render();
}

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CGameWorld::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam);
}