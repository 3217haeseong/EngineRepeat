#pragma once

#include <Windows.h>

namespace Utils
{
	template<typename T>
	void Swqp(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = a;
	}

	inline HANDLE GetConsoleHandle()
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}

	inline void SetConsolePosition(COORD coord)
	{
		static HANDLE handle = GetConsoleHandle;
		SetConsoleCursorPosition(handle, coord);
	}

	inline void SetConsoleTextColor(WORD color)
	{
		static HANDLE handle = GetConsoleHandle;
		SetConsoleTextAttribute(handle, color);
	}
}
