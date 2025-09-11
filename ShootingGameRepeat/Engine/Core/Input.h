#pragma once

#include "Core.h"
#include "Delegate.h"
#include "Math/Vector2.h"
#include <unordered_map>
#include <Windows.h>
#include <vector>

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

	Vector2 MousePosition() const;

	static Input& Get();

	template<typename T, void (T::*Method)()>
	void RegisterKeydownEvent(int keyCode, T* object)
	{
		if (!object)
		{
			OutputDebugStringA("일반 함수는 메소드 등록이 불가능합니다.");

			__debugbreak();
		}

		Delegate delegate(object, [](void* instance)
		{
			T* derived = static_cast<T*>(instance);
			(derived->*Method());
		});

		keydownCallbacks[keyCode].emplace_back(delegate);
	}

	template<typename T, void (T::*Method)()>
	void RegisterKeyupEvent(int keyCode, T* object)
	{
		if (!object)
		{
			OutputDebugStringA("일반 함수는 메소드 등록이 불가능합니다.");
			__debugbreak;
		}

		Delegate delegate(object, [](void* instance)
			{
				T* derived = static_cast<T*>(instance);
				(derived->*Method)();
			});

		keyupCallbacks[keyCode].emplace_back(delegate);
	}

	template<typename T, void (T::* Method)()>
	void RegisterKeyrepeatEvent(int keyCode, T* object)
	{
		if (!object)
		{
			OutputDebugStringA("일반 함수는 메소드 등옥이 불가능합니다.");

			__debugbreak();
		}

		Delegate delegate(object, [](void* instance)
			{
				T* derived = static_cast<T*>(instance);
				(derived->Method)();
			});

		keyrepeatCallbacks[keyCode].emplace_back(delegate);
	}

private:
	void ProcessInput();
	void DispatchCallbacks();
	void SavePreviousKeyStates();

private:
	KeyState keyStates[256] = {};

	Vector2 mousePosition;

	std::unordered_map<int, std::vector<Delegate>> keydownCallbacks;
	std::unordered_map<int, std::vector<Delegate>> keyupCallbacks;
	std::unordered_map<int, std::vector<Delegate>> keyrepeatCallbacks;

	static Input* instance;
};