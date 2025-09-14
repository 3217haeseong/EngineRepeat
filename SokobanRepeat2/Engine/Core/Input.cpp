#include "Input.h"
#include <Windows.h>

Input* Input::instance = nullptr;

Input::Input()
{
	instance = this;
}

void Input::ProcessInput()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].isKeyDown
			= GetAsyncKeyState(ix) & 0x8000;
	}
}

void Input::SavePreviousKeyStates()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].previousKeyDown
			= keyStates[ix].isKeyDown;
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
	return keyStates[keyCode].previousKeyDown
		&& !keyStates[keyCode].isKeyDown;
}

Input& Input::Get()
{
	return *instance;
}