#pragma once

// dll �ܺη� ���ø� ������ �� �߻��ϴ� ��� ��Ȱ��ȭ.
#pragma warning(disable : 4251)
// ���� ������ �ּҸ� ��ȯ�� �� �߻��ϴ� ��� ��Ȱ��ȭ.
#pragma warning(diable : 4172)

#if BuildEngineDLL
#define Engine_API __declspec(dllexport)
#else
#define Engine_API __declspec(dllimport)
#endif

template<typename T>
void SafeDelete(T*& target)
{
	if (target)
	{
		delete target;
		target = nullptr;
	}
}

template<typename T>
void SafeDeleteArray(T*& target)
{
	if (target)
	{
		delete[] target;
		target = nullptr;
	}
}