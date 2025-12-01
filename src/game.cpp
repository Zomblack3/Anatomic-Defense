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

		InitAudioDevice();

		const int amountOfButtonsMM = 4;
		const int amountOfButtonsOptions = 4;
		const int amountOfButtonsPause = 2;
		const int amountOfButtonsES = 2;
		const int amountOfButtonsExit = 2;

		Font font = LoadFont("res/fonts/ds_digital/DS-DIGIB.TTF");
		Font titleFont = LoadFont("res/fonts/Roboto/Roboto-Black.ttf");

		titleFont.baseSize = static_cast <int> (titleTextSize);

		Texture oldScreenTexture = LoadTexture("res/textures/screen_texture.jpg");
		Texture metalTexture = LoadTexture("res/textures/metal_texture.jpg");

		std::string textsOfMM[amountOfButtonsMM] = { "INICIAR", "OPCIONES", "CREDITOS", "SALIR" };
		std::string textsOfOptions[amountOfButtonsOptions] = { "TAMARINDO", "TANGAMANDAPIO", "TANGENTE", "VOLVER AL MENU" };
		std::string textsOfPause[amountOfButtonsPause] = { "VOLVER A LA PARTIDA", "VOLVER AL MENU" };
		std::string textsOfES[amountOfButtonsES] = { "REINICIAR", "VOLVER AL MENU" };
		std::string textsOfExit[amountOfButtonsExit] = { "SI", "NO" };

		Button buttonsMM[amountOfButtonsMM] = { };
		Button buttonsOptions[amountOfButtonsOptions] = { };
		Button buttonsPause[amountOfButtonsPause] = { };
		Button buttonsES[amountOfButtonsES] = { };
		Button buttonsExit[amountOfButtonsExit] = { };

		buttonsFeatures::setButtons(buttonsMM, amountOfButtonsMM, screenWidth - (screenWidth / 4.0f), (screenHeight / 2.0f) - 100, textsOfMM, SCREEN::MAIN_MENU, oldScreenTexture, metalTexture);
		buttonsFeatures::setButtons(buttonsOptions, amountOfButtonsOptions, screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 100, textsOfOptions, SCREEN::OPTIONS, oldScreenTexture, metalTexture);
		buttonsFeatures::setButtons(buttonsPause, amountOfButtonsPause, screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 50, textsOfPause, SCREEN::GAMEPLAY, oldScreenTexture, metalTexture);
		buttonsFeatures::setButtons(buttonsES, amountOfButtonsES, screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 50, textsOfES, SCREEN::END_SCREEN, oldScreenTexture, metalTexture);
		buttonsFeatures::setButtons(buttonsExit, amountOfButtonsExit, screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 50, textsOfExit, SCREEN::EXIT, oldScreenTexture, metalTexture);

		SCREEN currentScreen = SCREEN::MAIN_MENU;

		Texture MMBackground = { };
		Texture gameplayBackground = { };

		Texture smallEnemy = { };
		Texture mediumEnemy = { };
		Texture bigEnemy = { };

		Texture tutorialLeft = { };
		Texture tutorialRight = { };

		Sound playerShotSound = { };

		std::string titleText = "ANATOMIC DEFENSE";

		Vector2 titleLenght = MeasureTextEx(titleFont, titleText.c_str(), titleTextSize, textSpacing);
		
		Rectangle titleRec = { };
		Vector2 titlePos = { };

		titleRec.width = titleLenght.x + 40.0f;
		titleRec.height = titleLenght.y + 20.0f;
		titleRec.x = screenWidth / 2.0f - titleRec.width / 2.0f;
		titleRec.y = screenHeight / 7.0f;

		titlePos.x = screenWidth / 2.0f - titleLenght.x / 2.0f;
		titlePos.y = titleRec.y + (titleRec.height / 6.0f);

		Player player;

		std::vector <Enemy> enemies = { };

		player.pos = { screenWidth / 2.0f, screenHeight / 2.0f };
		player.height = (player.size / 2) / tanf(20 * DEG2RAD);

		resources::loadResources(MMBackground, gameplayBackground, player.texture, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, player.shotSound);

		while (!WindowShouldClose())
		{
			switch (currentScreen)
			{
			case SCREEN::MAIN_MENU:

				BeginDrawing();

				ClearBackground(BLACK);

				DrawTexture(MMBackground, 0, 0, WHITE);

				DrawRectangle(static_cast <int> (titleRec.x), static_cast <int> (titleRec.y), static_cast <int> (titleRec.width), static_cast <int> (titleRec.height), RED);
				DrawTextEx(titleFont, titleText.c_str(), titlePos, titleTextSize, textSpacing, WHITE);

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

				mainFunctions::gameplay(player, enemies, buttonsPause, amountOfButtonsPause, currentScreen, font, gameplayBackground, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight);

				break;
			case SCREEN::END_SCREEN:

				CloseAudioDevice();

				CloseWindow();

				break;
			case SCREEN::OPTIONS:



				break;
			case SCREEN::EXIT:

				CloseAudioDevice();

				CloseWindow();

				break;
			default:
				break;
			}
		}

		resources::unloadResources(font, MMBackground, gameplayBackground, player.texture, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, playerShotSound);
	}
}

namespace resources
{
	void loadResources(Texture& MMBackground, Texture& gameplayBackground, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShotSound)
	{
		const int sizeOfMediumEnemy = 50;
		const int sizeOfBigEnemy = 120;

		playerShotSound = LoadSound("res/sound_efects/player/player_shot.wav");

		Image MMBackroundImage = LoadImage("res/textures/main_menu/background.png");

		Image mediumEnemyImage = LoadImage("res/textures/gameplay/virus_medium.png");
		Image bigEnemyImage = LoadImage("res/textures/gameplay/virus_big.png");

		ImageResize(&MMBackroundImage, screenWidth, screenHeight);
		ImageResize(&mediumEnemyImage, sizeOfMediumEnemy, sizeOfMediumEnemy);
		ImageResize(&bigEnemyImage, sizeOfBigEnemy, sizeOfBigEnemy);

		MMBackground = LoadTextureFromImage(MMBackroundImage);
		gameplayBackground = LoadTexture("res/textures/gameplay/background.png");

		playerTexture = LoadTexture("res/textures/gameplay/player.png");
		
		smallEnemy = LoadTexture("res/textures/gameplay/virus_small.png");
		mediumEnemy = LoadTextureFromImage(mediumEnemyImage);
		bigEnemy = LoadTextureFromImage(bigEnemyImage);
		
		tutorialLeft = LoadTexture("res/textures/gameplay/left_click_tutorial.png");
		tutorialRight = LoadTexture("res/textures/gameplay/right_click_tutorial.png");

		areAssetsReady = true;

		UnloadImage(MMBackroundImage);
	}

	void unloadResources(Font& font, Texture& MMBackground, Texture& gameplayBackground, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShot)
	{
		// Font
		UnloadFont(font);

		// Sounds
		UnloadSound(playerShot);

		// Textures
		UnloadTexture(MMBackground);
		UnloadTexture(gameplayBackground);
		UnloadTexture(playerTexture);
		UnloadTexture(smallEnemy);
		UnloadTexture(mediumEnemy);
		UnloadTexture(bigEnemy);
		UnloadTexture(tutorialLeft);
		UnloadTexture(tutorialRight);
	}
}