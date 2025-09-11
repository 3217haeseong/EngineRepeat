#pragma once

#include "Core.h"

using Function = void(*)(void*);

struct Engine_API Delegate
{
	void* instance = nullptr;

	Function function = nullptr;

	Delegate() = default;

	Delegate(void* const instance, Function function)
		: instance(instance), function(function)
	{

	}

	void Invoke()
	{
		if (!instance || !function)
		{
			return;
		}

		function(instance);
	}

	void operator()()
	{
		Invoke();
	}
};