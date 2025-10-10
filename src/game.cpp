#include "game.h"

using namespace settings;

namespace run
{
	void game()
	{
		Screen currentScreen = Screen::MAIN_MENU;

		InitWindow(screenWidth, screenHeight, "Anatomic Defense");

		while (!WindowShouldClose())
		{
			switch (currentScreen)
			{
			case Screen::MAIN_MENU:

				

				break;
			case Screen::GAMEPLAY:



				break;
			case Screen::WIN_SCREEN:



				break;
			case Screen::LOSE_SCREEN:



				break;
			case Screen::OPTIONS:



				break;
			case Screen::EXIT:



				break;
			default:
				break;
			}
		}
	}
}
