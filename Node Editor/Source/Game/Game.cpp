#include "stdafx.h"
#include <tga2d/Engine.h>
#include "Game.h"

#include <tga2d/error/error_manager.h>

#include "GameObject.h"
#include "GameObjectManager.h"

using namespace std::placeholders;

#ifdef _DEBUG
#pragma comment(lib,"TGA2D_Debug.lib")
std::wstring BUILD_NAME = L"Debug";
#endif // DEBUG
#ifdef _RELEASE
#pragma comment(lib,"TGA2D_Release.lib")
std::wstring BUILD_NAME = L"Release";
#endif // DEBUG
#ifdef _RETAIL
#pragma comment(lib,"TGA2D_Retail.lib")
std::wstring BUILD_NAME = L"Retail";
#endif // DEBUG

CGame::CGame()
{
}


CGame::~CGame()
{
}

void CGame::Update(float aDeltaTime)
{
	
}

LRESULT CGame::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (myGameWorld.WinProc(hWnd, message, wParam, lParam))
	{
		return true;
	}
	lParam;
	wParam;
	hWnd;
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	}
	}

	return 0;
}



bool CGame::Init(const std::wstring& aVersion, HWND /*aHWND*/)
{
	UNREFERENCED_PARAMETER(aVersion);
    Tga2D::SEngineCreateParameters createParameters;
    
    createParameters.myInitFunctionToCall = std::bind( &CGame::InitCallBack, this );
	createParameters.myWinProcCallback = std::bind(&CGame::WinProc, this, _1, _2, _3, _4);
    createParameters.myUpdateFunctionToCall = std::bind( &CGame::UpdateCallBack, this );
    createParameters.myApplicationName = L"TGA2D Node editor 1.0f!";
	createParameters.myActivateDebugSystems = 0;
			
	if (!Tga2D::CEngine::Start(createParameters))
    {
        ERROR_PRINT( "Fatal error! Engine could not start!" );
		system("pause");
		return false;
    }

	// End of program
	return true;
}

void CGame::InitCallBack()
{
    myGameWorld.Init();

	
}

void CGame::UpdateCallBack()
{
	myGameWorld.Update(Tga2D::CEngine::GetInstance()->GetDeltaTime());

}
