#include "Game.h"
#include "Level/MenuLevel.h"
#include "Level/SokobanLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;
	
	AddLevel(new SokobanLevel());

	menuLevel = new MenuLevel();
}

Game::~Game()
{
	CleanUp();
}

void Game::ToggleMenu()
{
	system("cls");

	showMenu = !showMenu;

	if (showMenu)
	{
		backLevel = mainLevel;

		mainLevel = menuLevel;
	}
	else
	{
		mainLevel = backLevel;
	}
}

void Game::CleanUp()
{
	if (showMenu)
	{
		SafeDelete(backLevel);
		mainLevel = nullptr;
	}

	SafeDelete(menuLevel);
	Engine::CleanUp();
}

Game& Game::Get()
{
	return *instance;
}