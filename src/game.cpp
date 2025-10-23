#include "game.h"

#include <math.h>

#include "gameplay.h"

#include "player.h"
#include "enemies.h"

using namespace settings;

namespace run
{
	void game()
	{
		Screen currentScreen = Screen::GAMEPLAY;

		Player player;

		std::vector <Enemy> enemies;

		player.position = { screenWidth / 2.0f, screenHeight / 2.0f };
		player.height = (player.size / 2) / tanf(20 * DEG2RAD);

		InitWindow(screenWidth, screenHeight, "Anatomic Defense");

		while (!WindowShouldClose())
		{
			switch (currentScreen)
			{
			case Screen::MAIN_MENU:

				

				break;
			case Screen::GAMEPLAY:

				gameplay::gameplay(player, enemies);

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
