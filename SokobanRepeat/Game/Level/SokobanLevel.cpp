#include "SokobanLevel.h"
#include "Utils/Utils.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Target.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"

#include <iostream>

SokobanLevel::SokobanLevel()
{
    ReadMapFile("Stage1.txt");
}

void SokobanLevel::Render()
{
    super::Render();

    if (isGameClear)
    {
        Utils::SetConsolePosition({ 30,0 });
        Utils::SetConsoleTextColor(
            static_cast<WORD>(Color::White)
        );

        std::cout << "Game Clear";
    }
}

void SokobanLevel::ReadMapFile(const char* filename)
{
    char filepath[256] = { };
    sprintf_s(filepath, 256, "../Assets/%s", filename);

    FILE* file = nullptr;
    fopen_s(&file, filepath, "rt");

    if (file == nullptr)
    {
        std::cout << "맵 파일 읽기 실패: " << filename << "\n";
        __debugbreak();
        return;
    }
    fseek(file, 0, SEEK_END);
     size_t fileSize = ftell(file);
     rewind(file);

     char* buffer = new char[fileSize + 1];
     memset(buffer, 0, fileSize + 1);
     size_t readSize = fread(buffer, sizeof(char), fileSize, file);

     int index = 0;
     int size = (int)readSize;

     Vector2 position;

     while (index < size)
     {
         char mapCharacter = buffer[index];
         ++index;

         if (mapCharacter == '\n')
         {
             ++position.y;
             position.x = 0;

             continue;
         }

         switch (mapCharacter)
         {
         case '#':
         case '1':
             AddActor(new Wall(position));
             break;
         case '.':
             AddActor(new Ground(position));
             break;
         case 'p':
             AddActor(new Ground(position));
             AddActor(new Player(position));
             break;
         case 'b':

             AddActor(new Ground(position));
             AddActor(new Box(position));
             break;
         case 't':
             AddActor(new Target(position));
             ++targetScore;

             break;
         }

         ++position.x;
     }

     delete[] buffer;

     fclose(file);
}

bool SokobanLevel::CheckGameClear()
{
    int currentScore = 0;

    std::vector<Actor*> targetActors;
    std::vector<Actor*> boxActors;
    for (Actor* const actor : actors)
    {
        if (actor->As<Target>())
        {
            targetActors.emplace_back(actor);
            continue;
        }

        if (actor->As<Box>())
        {
            boxActors.emplace_back(actor);
        }
    }

    for (Actor* const targetActor : targetActors)
    {
        for (Actor* const boxActor : boxActors)
        {
            if (targetActor->Position() == boxActor->Position())
            {
                ++currentScore;
            }
        }
    }

    return currentScore == targetScore;
}

bool SokobanLevel::CanPlayerMove(
    const Vector2& playerPosition,
    const Vector2& newPosition)
{
    if (isGameClear)
    {
        return false;
    }

    std::vector<Box*> boxActors;
    for (Actor* const actor : actors)
    {
        Box* box = actor->As<Box>();
        if (box)
        {
            boxActors.emplace_back(box);
        }
    }

    Box* searchedBox = nullptr;
    for (Box* const boxActor : boxActors)
    {
        if (boxActor->Position() == newPosition)
        {
            searchedBox = boxActor;
            break;
        }
    }

    if (searchedBox)
    {
        Vector2 direction = newPosition - playerPosition;
        Vector2 nextPosition = searchedBox->Position() + direction;

        for (Box* const otherBox : boxActors)
        {
            if (otherBox == searchedBox)
            {
                continue;
            }

            if (otherBox->Position() == nextPosition)
            {
                return false;
            }
        }

        for (Actor* const actor : actors)
        {
            if (actor->Position() == nextPosition)
            {
                if (actor->As<Wall>())
                {
                    return false;
                }

                if (actor->As<Ground>() || actor->As<Target>())
                {
                    searchedBox->SetPosition(nextPosition);

                    isGameClear = CheckGameClear();

                    return true;
                }
            }
        }
    }

    for (Actor* const actor : actors)
    {
        if (actor->Position() == newPosition)
        {
            if (actor->As<Wall>())
            {
              return false;
            }

            return true;
        }
    }

    return false;
}
