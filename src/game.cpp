#include "game.h"

#include <math.h>

#include "settings.h"

#include "gameplay.h"

namespace run
{
	void game()
	{
		InitWindow(screenWidth, screenHeight, "Anatomic Defense");

		const int amountOfButtonsMM = 4;
		const int amountOfButtonsOptions = 4;
		const int amountOfButtonsPause = 2;
		const int amountOfButtonsES = 2;
		const int amountOfButtonsExit = 2;

		std::string textsOfMM[amountOfButtonsMM] = { "INICIAR", "OPCIONES", "CREDITOS", "SALIR" };
		std::string textsOfOptions[amountOfButtonsOptions] = { "TAMARINDO", "TANGAMANDAPIO", "TANGENTE", "VOLVER AL MENU" };
		std::string textsOfPause[amountOfButtonsPause] = { "VOLVER A LA PARTIDA", "VOLVER AL MENU" };
		std::string textsOfES[amountOfButtonsES] = { "REINICIAR", "VOLVER AL MENU" };
		std::string textsOfExit[amountOfButtonsExit] = { "SI", "NO" };

		Button buttonsMM[amountOfButtonsMM];
		Button buttonsOptions[amountOfButtonsOptions];
		Button buttonsPause[amountOfButtonsPause];
		Button buttonsES[amountOfButtonsES];
		Button buttonsExit[amountOfButtonsExit];

		buttonsFeatures::setButtons(buttonsMM, amountOfButtonsMM, screenWidth - (screenWidth / 4.0f), (screenHeight / 2.0f) - 100, textsOfMM, SCREEN::MAIN_MENU);
		buttonsFeatures::setButtons(buttonsOptions, amountOfButtonsOptions, screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 100, textsOfOptions, SCREEN::OPTIONS);
		buttonsFeatures::setButtons(buttonsPause, amountOfButtonsPause, screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 50, textsOfPause, SCREEN::GAMEPLAY);
		buttonsFeatures::setButtons(buttonsES, amountOfButtonsES, screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 50, textsOfES, SCREEN::END_SCREEN);
		buttonsFeatures::setButtons(buttonsExit, amountOfButtonsExit, screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 50, textsOfExit, SCREEN::EXIT);

		SCREEN currentScreen = SCREEN::MAIN_MENU;

		Texture MMBackground = { };
		Image gameplayBackground = { };

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
