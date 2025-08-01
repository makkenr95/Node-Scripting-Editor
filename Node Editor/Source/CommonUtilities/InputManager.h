#pragma once
#include <array>
#include <Windows.h>
#include <vector>

namespace CommonUtilities
{
	class InputManager
	{
		struct InputInfo
		{
			bool isDown = false;
			bool isPressed = false;
		};

	public:
		//void Update();
		InputManager();

		bool IsKeyDown(const int aKeyCode) const;
		bool IsKeyPressed(const int aKeyCode) const;
		bool UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam);
		bool IsKeyUp(const int aKeyCode) const;
		void SetCursorPosition(const int x, const int y);
		void EnableCursor();
		void DisableCursor(HWND hWnd);
		void ConfineCursor(HWND hwnd);
		void FreeCursor();

		//void Update();

		/*bool IsKeyReleased(const int aKeyCode);
		void AddKeyToVector(const int aKeyCode);
		void RemoveKeyFromVector(const int aKeyCode);*/
		POINT GetCursorPosition();
		POINT GetCursorMovement();
		bool IsLeftMouseButtonDown();
		bool IsRightMouseButtonDown();
		bool IsMiddleMouseButtonDown();
	private:
		POINT myLastCursorPoint;
		POINT myCursorPoint;
		std::array<InputInfo, 256> myKeyInfo;
		UINT myMessage;
		WPARAM myWparam;
		LPARAM myLparam;
	};
}

namespace CU = CommonUtilities;
