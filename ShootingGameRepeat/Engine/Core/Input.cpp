#include "Input.h"
#include "Engine.h"
#include "Windows.h"

Input* Input::instance = nullptr;

Input::Input()
{
	instance = this;
}

void Input::ProcessInput()
{
	static HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);
	static bool initialized = false;
	if (!initialized)
	{
		DWORD mode = ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
		mode &= ~ENABLE_QUICK_EDIT_MODE;
		BOOL result = SetConsoleMode(inputHandle, mode);

		if (result == FALSE)
		{
			int errorCode = GetLastError();
			OutputDebugStringA("마우스 입력 설정 실패\n");
			__debugbreak();
		}

		initialized = true;
	}

	const int recordCount = 256;
	INPUT_RECORD records[recordCount] = {};
	DWORD eventReadCount = 0;

	if (PeekConsoleInput(inputHandle, records, recordCount, &eventReadCount) && eventReadCount > 0)
	{
		if (ReadConsoleInput(inputHandle, records, recordCount, &eventReadCount))
		{
			for (int ix = 0; ix < (int)eventReadCount; ++ix)
			{
				INPUT_RECORD& record = records[ix];

				switch (record.EventType)
				{
				case KEY_EVENT:
				{
					if (record.Event.KeyEvent.bKeyDown)
					{
						keyStates[record.Event.KeyEvent.wVirtualKeyCode].isKeyDown = true;
					}
					else
					{
						keyStates[record.Event.KeyEvent.wVirtualKeyCode].isKeyDown = false;
					}
				}
				break;

				case MOUSE_EVENT:
				{
					mousePosition.x = record.Event.MouseEvent.dwMousePosition.X;
					mousePosition.x = mousePosition.x < 0 ? 0
						: mousePosition.x >= Engine::Get().Width() - 1 ? Engine::Get().Width() - 1
						: mousePosition.x;
					mousePosition.y = record.Event.MouseEvent.dwMousePosition.X;
					mousePosition.y = mousePosition.y < 0 ? 0
						: mousePosition.y >= Engine::Get().Height() - 1 ? Engine::Get().Height() - 1
						: mousePosition.y;

					keyStates[VK_LBUTTON].isKeyDown
						= (record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) != 0;

					keyStates[VK_RBUTTON].isKeyDown
						= (record.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) != 0;
				}
				break;
				}
			}
		}
	}
}

void Input::DispatchCallbacks()
{
	if (keydownCallbacks.size() > 0)
	{
		for (std::pair<const int, std::vector<Delegate>>& pair : keydownCallbacks)
		{
			if (GetKeyDown(pair.first))
			{
				for (Delegate& delegate : pair.second)
				{
					delegate();
				}
			}
		}
	}

	if (keyupCallbacks.size() > 0)
	{
		for (std::pair<const int, std::vector<Delegate>>& pair : keyupCallbacks)
		{
			if (GetKeyUp(pair.first))
			{
				for (Delegate& delegate : pair.second)
				{
					delegate();
				}
			}
		}
	}

	if (keyrepeatCallbacks.size() > 0)
	{
		for (std::pair<const int, std::vector<Delegate>>& pair : keyrepeatCallbacks)
		{
			if (GetKey(pair.first))
			{
				for (Delegate& delegate : pair.second)
				{
					delegate();
				}
			}
		}
	}
}

void Input::SavePreviousKeyStates()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].previousKeyDown = keyStates[ix].isKeyDown;
	}
}

bool Input::GetKey(int keyCode)
{
	return keyStates[keyCode].isKeyDown;
}

bool Input::GetKeyDown(int keyCode)
{
	return keyStates[keyCode].isKeyDown && !keyStates[keyCode].previousKeyDown;
}

bool Input::GetKeyUp(int keyCode)
{
	return keyStates[keyCode].previousKeyDown && !keyStates[keyCode].isKeyDown;
}

Vector2 Input::MousePosition() const
{
	return Vector2();
}

Input& Input::Get()
{
	return *instance;
}