#include "game.h"

#include <math.h>

#include "settings.h"

#include "gameplay.h"

bool areAssetsReady = false;

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

		Font font = LoadFont("res/fonts/robot_crush/Robot Crush.ttf");

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

		buttonsFeatures::setButtons(buttonsMM, amountOfButtonsMM, screenWidth - (screenWidth / 4.0f), (screenHeight / 2.0f) - 100, textsOfMM, SCREEN::MAIN_MENU, font);
		buttonsFeatures::setButtons(buttonsOptions, amountOfButtonsOptions, screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 100, textsOfOptions, SCREEN::OPTIONS, font);
		buttonsFeatures::setButtons(buttonsPause, amountOfButtonsPause, screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 50, textsOfPause, SCREEN::GAMEPLAY, font);
		buttonsFeatures::setButtons(buttonsES, amountOfButtonsES, screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 50, textsOfES, SCREEN::END_SCREEN, font);
		buttonsFeatures::setButtons(buttonsExit, amountOfButtonsExit, screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 50, textsOfExit, SCREEN::EXIT, font);

		SCREEN currentScreen = SCREEN::MAIN_MENU;

		Image gameplayBackgroundImage = { };

		Texture MMBackground = { };
		Texture gameplayBackground = { };

		Texture smallEnemy = { };
		Texture mediumEnemy = { };
		Texture bigEnemy = { };

		Texture tutorialLeft = { };
		Texture tutorialRight = { };

		Sound playerShotSound = { };

		std::string titleText = "ANATOMIC DEFENSE";
		Vector2 titleLenght = MeasureTextEx(font, titleText.c_str(), 50, 2);
		
		Rectangle titleRec = { };
		Vector2 titlePos = { };
		titleRec.x = 50.0f;
		titleRec.y = 50.0f;
		titleRec.width = static_cast <float> (titleText.size()) * 50;
		titleRec.height = 70.0f;
		titlePos.x = (titleRec.x + (titleRec.width / 2.0f)) - titleLenght.x / 2.0f;
		titlePos.y = titleRec.y + (titleRec.height / 2.0f);

		Player player;

		std::vector <Enemy> enemies;

		int frames = 0;

		player.pos = { screenWidth / 2.0f, screenHeight / 2.0f };
		player.height = (player.size / 2) / tanf(20 * DEG2RAD);

		resources::loadResources(MMBackground, gameplayBackground, gameplayBackgroundImage, player.texture, frames, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, player.shotSound);

		while (!WindowShouldClose())
		{
			switch (currentScreen)
			{
			case SCREEN::MAIN_MENU:

				BeginDrawing();

				ClearBackground(BLACK);

				DrawTexture(MMBackground, 0, 0, WHITE);

				DrawRectangle(static_cast <int> (titleRec.x), static_cast <int> (titleRec.y), static_cast <int> (titleRec.width), static_cast <int> (titleRec.height), WHITE);
				//DrawText(titleText.c_str(), static_cast <int> ((titleRec.x + (titleRec.width / 2.0f)) - titleLenght / 2.0f), static_cast <int> (titleRec.y + 25), 50, BLACK);
				DrawTextEx(font, titleText.c_str(), titlePos, 50, 2, BLACK);

				buttonsFeatures::drawButtons(buttonsMM, amountOfButtonsMM, font);

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

				DrawText("Creado por Zomblack3 (Santiago Britos)", 0, static_cast <int> (screenHeight) - 30, 30, BLACK);

				EndDrawing();

				break;
			case SCREEN::GAMEPLAY:

				gameplay::gameplay(player, enemies, buttonsPause, amountOfButtonsPause, currentScreen, font, gameplayBackgroundImage, gameplayBackground, smallEnemy, mediumEnemy, bigEnemy, frames, tutorialLeft, tutorialRight);

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

		resources::unloadResources(font, MMBackground, gameplayBackground, gameplayBackgroundImage, player.texture, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, playerShotSound);
	}
}

namespace resources
{
	void loadResources(Texture& MMBackground, Texture& gameplayBackground, Image& backgroundAnim, Texture& playerTexture, int& frames, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShotSound)
	{
		int loadingText = MeasureText("Cargando Recursos", 30);

		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("Cargando Recursos", (screenWidth / 2) - (loadingText / 2), static_cast <int> (screenHeight) / 2, 30, WHITE);

		EndDrawing();

		//frames = 0;

		playerShotSound = LoadSound("res/sound_efects/player/player_shot.wav");

		Image MMBackroundImage = LoadImage("res/textures/main_menu/background.png");
		backgroundAnim = LoadImageAnim("res/textures/gameplay/background.gif", &frames);
		//backgroundAnim = LoadImage("res/textures/gameplay/player.png");
		Image mediumEnemyImage = LoadImage("res/textures/gameplay/virus_medium.png");
		Image bigEnemyImage = LoadImage("res/textures/gameplay/virus_big.png");

		ImageResize(&MMBackroundImage, screenWidth, screenHeight);
		ImageResize(&mediumEnemyImage, 50, 50);
		ImageResize(&bigEnemyImage, 120, 120);

		MMBackground = LoadTextureFromImage(MMBackroundImage);
		gameplayBackground = LoadTextureFromImage(backgroundAnim);
		//gameplayBackground = LoadTexture("res/textures/gameplay/player.png");
		playerTexture = LoadTexture("res/textures/gameplay/player.png");
		smallEnemy = LoadTexture("res/textures/gameplay/virus_small.png");
		mediumEnemy = LoadTextureFromImage(mediumEnemyImage);
		bigEnemy = LoadTextureFromImage(bigEnemyImage);
		tutorialLeft = LoadTexture("res/textures/gameplay/left_click_tutorial.png");
		tutorialRight = LoadTexture("res/textures/gameplay/right_click_tutorial.png");

		areAssetsReady = true;

		UnloadImage(MMBackroundImage);
	}

	void unloadResources(Font& font, Texture& MMBackground, Texture& gameplayBackground, Image& backgroundAnim, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShot)
	{
		UnloadFont(font);
		UnloadSound(playerShot);
		UnloadTexture(MMBackground);
		UnloadTexture(gameplayBackground);
		UnloadTexture(playerTexture);
		UnloadTexture(smallEnemy);
		UnloadTexture(mediumEnemy);
		UnloadTexture(bigEnemy);
		UnloadTexture(tutorialLeft);
		UnloadTexture(tutorialRight);
		UnloadImage(backgroundAnim);
	}
}