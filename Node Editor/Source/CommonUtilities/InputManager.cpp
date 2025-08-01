#include "pch.h"
#include "InputManager.h"
#include <bitset>

CommonUtilities::InputManager::InputManager() : myLastCursorPoint(), myCursorPoint(), myMessage(0), myWparam(0),
												myLparam(0)
{
}

bool CU::InputManager::IsKeyDown(const int aKeyCode) const
{
	return myKeyInfo[aKeyCode].isDown;
}

bool CU::InputManager::IsKeyPressed(const int aKeyCode) const
{
	return myKeyInfo[aKeyCode].isPressed;
}

bool CU::InputManager::UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam)
{
	myMessage = message;
	myWparam = wParam;
	myLparam = lParam;
	switch (message)
	{
	case WM_KEYDOWN:
		if (myKeyInfo[wParam].isPressed)
		{
			myKeyInfo[wParam].isDown = false;
		}
		else
		{
			myKeyInfo[wParam].isDown = true;
		}
		myKeyInfo[wParam].isPressed = std::bitset<32>(lParam).test(30);
		return true;
	case WM_KEYUP:
		myKeyInfo[wParam].isPressed = false;
		myKeyInfo[wParam].isDown = false;
		return true;
	case WM_MOUSEMOVE:
		myLastCursorPoint = myCursorPoint;
		myCursorPoint = GetCursorPosition();
		RECT rect;
		GetClientRect(GetActiveWindow(), &rect);

		POINT ul;
		ul.x = rect.left;
		ul.y = rect.top;

		POINT lr;
		lr.x = rect.right;
		lr.y = rect.bottom;

		MapWindowPoints(GetActiveWindow(), nullptr, &ul, 1);
		MapWindowPoints(GetActiveWindow(), nullptr, &lr, 1);

		rect.left = ul.x;
		rect.top = ul.y - 50;

		rect.right = lr.x;
		rect.bottom = lr.y;

		ClipCursor(&rect);
		return true;
	default:
		/*myKeyInfo[wParam].isPressed = false;
		myKeyInfo[wParam].isDown = false;*/
		break;
	}
	return false;
}

bool CU::InputManager::IsKeyUp(const int aKeyCode) const
{
	if (aKeyCode == myWparam)
	{
		if (myMessage == WM_KEYUP)
		{
			return true;
		}
	}
	return false;
}

void CommonUtilities::InputManager::SetCursorPosition(const int x, const int y)
{
	SetCursorPos(x, y);
}

POINT CU::InputManager::GetCursorPosition()
{
	GetCursorPos(&myCursorPoint);
	ScreenToClient(GetActiveWindow(), &myCursorPoint);
	return myCursorPoint;
}

POINT CU::InputManager::GetCursorMovement()
{
	POINT cursorPoint = GetCursorPosition();
	cursorPoint.x -= myLastCursorPoint.x;
	cursorPoint.y -= myLastCursorPoint.y;
	myLastCursorPoint = GetCursorPosition();
	return cursorPoint;
}

bool CU::InputManager::IsLeftMouseButtonDown()
{
	return (GetAsyncKeyState(0x01));
}

bool CU::InputManager::IsRightMouseButtonDown()
{
	return (GetAsyncKeyState(0x02));
}

bool CU::InputManager::IsMiddleMouseButtonDown()
{
	return (GetAsyncKeyState(0x04));
}
void CU::InputManager::EnableCursor()
{
	while (::ShowCursor(TRUE) < 0);
	FreeCursor();
}

void CU::InputManager::DisableCursor(HWND hWnd)
{
	while (::ShowCursor(FALSE) >= 0);
	ConfineCursor(hWnd);
}

void CU::InputManager::ConfineCursor(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	MapWindowPoints(hWnd, nullptr, reinterpret_cast<POINT*>(&rect), 2);
	ClipCursor(&rect);
}

void CU::InputManager::FreeCursor()
{
	ClipCursor(nullptr);
}
//void CommonUtilities::InputManager::Update()
//{
//	for (int i = 0; i < myKeyInfo.size(); i++)
//	{
//		if (GetAsyncKeyState(i))
//		{
//			if (myKeyInfo[i].isPressed)
//			{
//
//			}
//			else if (myKeyInfo[i].isDown)
//			{
//				myKeyInfo[i].isPressed = true;
//				myKeyInfo[i].isDown = false;
//			}
//			else
//			{
//				myKeyInfo[i].isDown = true;
//			}
//		}
//		else
//		{
//			myKeyInfo[i].isPressed = false;
//			myKeyInfo[i].isDown = false;
//		}
//	}
//}
//

//void CommonUtilities::UpdateEvents::Update()
//{
//	for (int i = 0; i < myKeysPressed.size(); i++)
//	{
//		if (GetAsyncKeyState(myKeysPressed[i]))
//		{
//
//		}
//		else
//		{
//			myKeysPressed.erase(myKeysPressed.begin() + i);
//			i--;
//		}
//	}
//}
//
//bool CommonUtilities::UpdateEvents::IsKeyDown(const int aKeyCode)
//{
//	if (GetAsyncKeyState(aKeyCode) && !IsKeyPressed(aKeyCode))
//	{
//		AddKeyToVector(aKeyCode);
//		return true;
//	}
//	return false;
//}
//
//bool CommonUtilities::UpdateEvents::IsKeyPressed(const int aKeyCode)
//{
//	if (GetAsyncKeyState(aKeyCode))
//	{
//		AddKeyToVector(aKeyCode);
//		return true;
//	}
//	for (int key : myKeysPressed)
//	{
//		if (key == aKeyCode)
//		{
//			return true;
//		}
//	}
//	return false;
//}
//
//bool CommonUtilities::UpdateEvents::IsKeyReleased(const int aKeyCode)
//{
//	if (aKeyCode == my)
//	{
//
//
//	}
//	/*
//	if (!GetAsyncKeyState(aKeyCode) && IsKeyPressed(aKeyCode))
//	{
//		return true;
//	}
//	return false;*/
//}
//
//void UpdateEvents::AddKeyToVector(const int aKeyCode)
//{
//	myKeysPressed.push_back(aKeyCode);
//}
//
//void UpdateEvents::RemoveKeyFromVector(const int aKeyCode)
//{
//	for (int i = 0; i < myKeysPressed.size(); ++i)
//	{
//		if (aKeyCode == myKeysPressed[i])
//		{
//			myKeysPressed.erase(myKeysPressed.begin() + i);
//			return;
//		}
//	}
//}
//
