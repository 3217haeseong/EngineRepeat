#include "Engine.h"
#include <iostream>
#include <Windows.h>

#include "Utils/Utils.h"

Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
    switch (CtrlType)
    {
    case CTRL_CLOSE_EVENT:
        Engine::Get().CleanUp();
        return false;
    }

    return false;
}



Engine::Engine()
{
    instance = this;

    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 1;

    SetConsoleCursorInfo(
        GetStdHandle(STD_OUTPUT_HANDLE),
        &info
    );

    LoadEngineSettings();

    srand(static_cast<unsigned int>(time(nullptr)));

    Vector2 screenSize(settings.width, settings.height);
    imageBuffer = new ImageBuffer((screenSize.x + 1) * (screenSize.y + 1));

    ClearImageBuffer();
}

Engine::~Engine()
{
    CleanUp();
}

void Engine::Run()
{
    LARGE_INTEGER currentTime;
    LARGE_INTEGER previousTime;
    QueryPerformanceCounter(&currentTime);
    previousTime = currentTime;

    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
}

void Engine::WriteToBuffer(const Vector2& position, const char* image, Color color, int sortingOrder)
{
}

void Engine::PresentImmediately()
{
}

void Engine::AddLevel(Level* newLevel)
{
}

void Engine::ChangeLevel(Level* newLevel)
{
}

void Engine::CleanUp()
{
}

void Engine::Quit()
{
}

Engine& Engine::Get()
{
    // TODO: 여기에 return 문을 삽입합니다.
}

int Engine::Width() const
{
    return 0;
}

int Engine::Height() const
{
    return 0;
}

void Engine::OnInitialized()
{
}

void Engine::DisableToResizeWindow()
{
}

void Engine::BeginPlay()
{
}

void Engine::Tick(float deltaTime)
{
}

void Engine::Clear()
{
}

void Engine::Render()
{
}

void Engine::Present()
{
}

void Engine::LoadEngineSettings()
{
    FILE* file = nullptr;
    fopen_s(&file, "../Settings/EngineSettings.txt", "rt");
    if (file == nullptr)
    {
        std::cout << "Failed to load engine settings.\n";
        __debugbreak();
        return;
    }

    fseek(file, 0, SEEK_END);

    size_t fileSize = ftell(file);

    rewind(file);

    char* buffer = new char[fileSize + 1];
    memset(buffer, 0, fileSize + 1);

    size_t readSize = fread(buffer, sizeof(char), fileSize, file);

    char* context = nullptr;
    char* token = nullptr;

    token = strtok_s(buffer, "\n", &context);

    while (token != nullptr)
    {
        char header[10] = {};
        
        sscanf_s(token, "%s", header, 10);

        if (strcmp(header, "framerate") == 0)
        {
            sscanf_s(token, "framerate = %f", &settings.framerate);
        }
        else if (strcmp(header, "width") == 0)
        {
            sscanf_s(token, "width = %d", &settings.width);
        }
        else if (strcmp(header, "height") == 0)
        {
            sscanf_s(token, "height = %d", &settings.height);
        }

        token = strtok_s(nullptr, "\n", &context);
    }

    SafeDeleteArray(buffer);

    fclose(file);


}

ScreenBuffer* Engine::GetRenderer() const
{
    return nullptr;
}

void Engine::ClearImageBuffer()
{
    for (int y = 0; y < settings.height; ++y)
    {
        for (int x = 0; x < settings.width; ++x)
        {
            int index = (y * (settings.width)) + x;
            CHAR_INFO& buffer = imageBuffer->charInfoArray[index];
            buffer.Char.AsciiChar = ' ';
            buffer.Attributes = 0;
            imageBuffer->sortingOrderArray[index] = -1;
        }

        int index = (y * (settings.width)) + settings.width;
        CHAR_INFO& buffer = imageBuffer->charInfoArray[index];
        buffer.Char.AsciiChar = '\n';
        buffer.Attributes = 0;
        imageBuffer->sortingOrderArray[index] = -1;
    }
    int index = (settings.width) * settings.height + 1;
    CHAR_INFO& buffer = imageBuffer->charInfoArray[index];
    buffer.Char.AsciiChar = '\0';
    buffer.Attributes = 0;
    imageBuffer->sortingOrderArray[index] = -1;
}
