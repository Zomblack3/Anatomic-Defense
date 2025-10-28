#include "game.h"

#include <math.h>

#include "settings.h"

#include "gameplay.h"

namespace run
{
	void game()
	{
		Screen currentScreen = Screen::GAMEPLAY;

		Player player;

		Font font = { };

		std::vector <Enemy> enemies;

		player.pos = { screenWidth / 2.0f, screenHeight / 2.0f };
		player.height = (player.size / 2) / tanf(20 * DEG2RAD);

		InitWindow(screenWidth, screenHeight, "Anatomic Defense");

		while (!WindowShouldClose())
		{
			switch (currentScreen)
			{
			case SCREEN::MAIN_MENU:

				BeginDrawing();

				ClearBackground(BLACK);

				DrawTexture(MMBackground, 0, 0, WHITE);

				buttonsFeatures::drawButtons(buttonsMM, amountOfButtonsMM);

				for (int i = 0; i < amountOfButtonsMM; i++)
				{
					if (buttonsFeatures::collitionCheckButtonMouse(buttonsMM[i].rec))
					{
						buttonsFeatures::chageButtonState(buttonsMM[i]);

						if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
						{
							if (buttonsMM[i].directionScreen != currentScreen)
								currentScreen = buttonsMM[i].directionScreen;
						}
					}
				}

				EndDrawing();

				break;
			case SCREEN::GAMEPLAY:

				gameplay::gameplay(player, enemies, buttonsPause, amountOfButtonsPause, currentScreen, font, gameplayBackground);

				break;
			case SCREEN::END_SCREEN:

				CloseWindow();

				break;
			case SCREEN::OPTIONS:



				break;
			case SCREEN::EXIT:

				CloseWindow();

				break;
			default:
				break;
			}
		}
	}
}
