#pragma once

#include "Core.h"
#include "Input.h"
#include "Math/Color.h"
#include "Math/Vector2.h"

#include <Windows.h>

struct EngineSettings
{
	int width = 0;
	int height = 0;
	float framerate = 0.0f;
};

struct ImageBuffer
{
	ImageBuffer(int bufferCount)
	{
		charInfoArray = new CHAR_INFO[bufferCount];
		memset(charInfoArray, 0, sizeof(int) * bufferCount);
	}

	~ImageBuffer()
	{
		SafeDeleteArray(charInfoArray);
		SafeDeleteArray(sortingOrderArray);
	}

	CHAR_INFO* charInfoArray = nullptr;

	int* sortingOrderArray = nullptr;

};

class Level;
class ScreenBuffer;
class Engine_API Engine
{
public:
	Engine();
	virtual ~Engine();

	void Run();

	void WriteToBuffer(
		const Vector2& position, const char* image, Color color = Color::White,
		int sortingOrder = 0
	);

	void PresentImmediately();

	void AddLevel(Level* newLevel);

	void ChangeLevel(Level* newLevel);

	virtual void CleanUp();

	void Quit();

	static Engine& Get();

	int Width() const;
	int Height() const;

protected:

	virtual void OnInitialized();

	void DisableToResizeWindow();

	void BeginPlay();
	void Tick(float deltaTime = 0.0f);

	void Clear();

	void Render();

	void Present();

	void LoadEngineSettings();

	ScreenBuffer* GetRenderer() const;

	void ClearImageBuffer();

protected:
	bool isQuit = false;
	Level* mainLevel = nullptr;
	Level* nextLevel = nullptr;
	Input input;
	EngineSettings settings;

	ImageBuffer* imageBuffer = nullptr;

	ScreenBuffer* renderTargets[2] = {};
	int currentRenderTargetIndex = 0;

	static Engine* instance;

};