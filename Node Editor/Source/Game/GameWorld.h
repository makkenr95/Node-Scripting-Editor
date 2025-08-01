#pragma once

namespace Tga2D
{
	class CSprite;
}

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
	LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
};