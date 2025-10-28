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

		Image gameplayBackgroundImage = { };

		Texture MMBackground = { };
		Texture gameplayBackground = { };

		Texture smallEnemy = { };
		Texture mediumEnemy = { };
		Texture bigEnemy = { };

		Player player;

		Font font = { };

		std::vector <Enemy> enemies;

		int frames = 0;

		player.pos = { screenWidth / 2.0f, screenHeight / 2.0f };
		player.height = (player.size / 2) / tanf(20 * DEG2RAD);

		resources::loadResources(font, MMBackground, gameplayBackground, gameplayBackgroundImage, player.texture, frames, smallEnemy, mediumEnemy, bigEnemy);

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
					buttonsFeatures::chageButtonState(buttonsMM[i]);

					if (buttonsFeatures::collitionCheckButtonMouse(buttonsMM[i].rec))
					{
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

				gameplay::gameplay(player, enemies, buttonsPause, amountOfButtonsPause, currentScreen, font, gameplayBackgroundImage, gameplayBackground, smallEnemy, mediumEnemy, bigEnemy, frames);

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

		resources::unloadResources(font, MMBackground, gameplayBackground, gameplayBackgroundImage, player.texture, smallEnemy, mediumEnemy, bigEnemy);
	}
}

namespace resources
{
	void loadResources(Font& font, Texture& MMBackground, Texture& gameplayBackground, Image& backgroundAnim, Texture& playerTexture, int& frames, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy)
	{
		Image MMBackroundImage = LoadImage("res/textures/main_menu/background.png");
		backgroundAnim = LoadImageAnim("res/textures/gameplay/background.gif", &frames);
		//backgroundAnim = LoadImageAnim("res/textures/gameplay/scarfy_run.gif", &frames);
		Image mediumEnemyImage = LoadImage("res/textures/gameplay/virus_medium.png");
		Image bigEnemyImage = LoadImage("res/textures/gameplay/virus_big.png");

		ImageResize(&MMBackroundImage, screenWidth, screenHeight);
		//ImageResize(&backgroundAnim, screenWidth, screenHeight);
		ImageResize(&mediumEnemyImage, 50, 50);
		ImageResize(&bigEnemyImage, 120, 120);

		font = LoadFont("res/fonts/robot_crush/Robot Crush.ttf");
		MMBackground = LoadTextureFromImage(MMBackroundImage);
		gameplayBackground = LoadTextureFromImage(backgroundAnim);
		playerTexture = LoadTexture("res/textures/gameplay/player.png");
		smallEnemy = LoadTexture("res/textures/gameplay/virus_small.png");
		mediumEnemy = LoadTextureFromImage(mediumEnemyImage);
		bigEnemy = LoadTextureFromImage(bigEnemyImage);

		UnloadImage(MMBackroundImage);
	}

	void unloadResources(Font& font, Texture& MMBackground, Texture& gameplayBackground, Image& backgroundAnim, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy)
	{
		UnloadFont(font);
		UnloadTexture(MMBackground);
		UnloadTexture(gameplayBackground);
		UnloadTexture(playerTexture);
		UnloadTexture(smallEnemy);
		UnloadTexture(mediumEnemy);
		UnloadTexture(bigEnemy);
		UnloadImage(backgroundAnim);
	}
}