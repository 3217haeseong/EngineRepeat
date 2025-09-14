#pragma once

#include "Core.h"

class Engine_API Input
{
	friend class Engine;

	struct KeyState
	{
		bool isKeyDown = false;

		bool previousKeyDown = false;

	};

public:
	Input();

	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);

	static Input& Get();

private:
	void ProcessInput();
	void SavePreviousKeyStates();

private:
	KeyState keyStates[256] = {};

	static Input* instance;
};