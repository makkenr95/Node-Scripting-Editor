#pragma once
#include <tga2d/Engine.h>
#include <fstream>
#include "GameWorld.h"

class CGame
{
public:
	CGame();
	~CGame();

	void Update(float aDeltaTime);

	bool Init(const std::wstring& aVersion = L"", HWND aHWND = nullptr);
private:
	void InitCallBack();
	void UpdateCallBack();
	LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	CGameWorld myGameWorld;

};
