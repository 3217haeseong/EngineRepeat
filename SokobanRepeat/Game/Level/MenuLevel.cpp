#include "MenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"

#include <iostream>

MenuLevel::MenuLevel()
{
	items.emplace_back(new MenuItem(
		"Resume Game",
		[]() {Game::Get().ToggleMenu(); }
	));

	items.emplace_back(new MenuItem(
		"Quit Game",
		[]() {Game::Get().Quit(); }
	));

	length = static_cast<int>(items.size());
};

MenuLevel::~MenuLevel()
{
	for (MenuItem* item : items)
	{
		SafeDelete(item);
	}

	items.clear();
}

void MenuLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	// Enter Å° ÀÔ·Â.
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		items[currentIndex]->onSelected();
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();

		currentIndex = 0;
	}
}

void MenuLevel::Render()
{
	super::Render();

	Utils::SetConsolePosition({ 0,0 });
	Utils::SetConsoleTextColor(static_cast<WORD>(unselectedColor));

	std::cout << "SokobanGame\n\n";

	for (int ix = 0; ix < length; ++ix)
	{
		Color textColor = (ix == currentIndex) ? selectedColor : unselectedColor;

		Utils::SetConsoleTextColor(static_cast<WORD>(textColor));

		std::cout << items[ix]->menuText << "\n";
	}

}
