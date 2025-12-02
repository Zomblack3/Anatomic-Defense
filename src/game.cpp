#include "game.h"

#include <math.h>

#include "settings.h"

#include "gameplay.h"
#include "endGame.h"

bool areAssetsReady = false;

namespace run
{
	void game()
	{
		InitWindow(screenWidth, screenHeight, "Anatomic Defense");

		InitAudioDevice();

		const int amountOfButtonsMM = 3;
		const int amountOfButtonsPause = 2;
		const int amountOfButtonsEG = 2;
		const int amountOfButtonsExit = 2;

		Font baseFont = LoadFont("res/fonts/ds_digital/DS-DIGIB.TTF");
		Font titleFont = LoadFont("res/fonts/Roboto/Roboto-Black.ttf");

		titleFont.baseSize = static_cast <int> (titleTextSize);

		Texture oldScreenTexture = LoadTexture("res/textures/screen_texture.jpg");
		Texture metalTexture = LoadTexture("res/textures/metal_texture.jpg");

		std::string textsOfMM[amountOfButtonsMM] = { "INICIAR", "CREDITOS", "SALIR" };
		std::string textsOfPause[amountOfButtonsPause] = { "VOLVER A LA PARTIDA", "VOLVER AL MENU" };
		std::string textsOfEG[amountOfButtonsEG] = { "REINICIAR", "VOLVER AL MENU" };
		std::string textsOfExit[amountOfButtonsExit] = { "SI", "NO" };

		Button buttonsMM[amountOfButtonsMM] = { };
		Button buttonsPause[amountOfButtonsPause] = { };
		Button buttonsEG[amountOfButtonsEG] = { };
		Button buttonsExit[amountOfButtonsExit] = { };

		Vector2 buttonsStartingPosMM = { screenWidth - (screenWidth / 4.0f), (screenHeight / 2.0f) - 100.0f };
		Vector2 buttonsStartingPosOptions = { screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 100.0f };
		Vector2 buttonsStartingPosPause = { screenWidth / 2.0f, (screenHeight / 2.0f) - 50.0f };
		Vector2 buttonsStartingPosEG = { screenWidth / 2.0f, screenHeight / 2.0f + (screenHeight / 8.0f) };
		Vector2 buttonsStartingPosExit = { screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 50.0f };

		buttonsFeatures::setButtons(buttonsMM, amountOfButtonsMM, buttonsStartingPosMM.x, buttonsStartingPosMM.y, textsOfMM, SCREEN::MAIN_MENU, oldScreenTexture, metalTexture);
		buttonsFeatures::setButtons(buttonsPause, amountOfButtonsPause, buttonsStartingPosPause.x, buttonsStartingPosPause.y, textsOfPause, SCREEN::GAMEPLAY, oldScreenTexture, metalTexture);
		buttonsFeatures::setButtons(buttonsEG, amountOfButtonsEG, buttonsStartingPosEG.x, buttonsStartingPosEG.y, textsOfEG, SCREEN::END_GAME, oldScreenTexture, metalTexture);
		buttonsFeatures::setButtons(buttonsExit, amountOfButtonsExit, buttonsStartingPosExit.x, buttonsStartingPosExit.y, textsOfExit, SCREEN::EXIT, oldScreenTexture, metalTexture);

		metalTexture.width = hudWidth;
		metalTexture.height = hudHeight;

		SCREEN currentScreen = SCREEN::MAIN_MENU;

		Texture MMBackground = { };
		Texture gameplayBackground = { };
		Texture EGBackground = { };

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

		playerFeatures::setDefault(player);

		std::vector <Enemy> enemies = { };

		resources::loadResources(MMBackground, gameplayBackground, player.texture, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, player.shotSound, EGBackground);

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

				buttonsFeatures::drawButtons(buttonsMM, amountOfButtonsMM, baseFont);

				// Update
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

				DrawText("Creado por Zomblack3 (Santiago Britos)", 10, static_cast <int> (screenHeight) - 30, 30, BLACK);

				EndDrawing();

				break;
			case SCREEN::GAMEPLAY:

				mainFunctions::gameplay(player, enemies, buttonsPause, amountOfButtonsPause, currentScreen, baseFont, gameplayBackground, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, metalTexture, oldScreenTexture);

				break;
			case SCREEN::END_GAME:

				mainFunctions::endGame(player, enemies, buttonsEG, amountOfButtonsEG, currentScreen, titleFont, baseFont, EGBackground);

				break;
			case SCREEN::EXIT:

				CloseAudioDevice();

				CloseWindow();

				break;
			default:
				break;
			}
		}

		resources::unloadResources(baseFont, MMBackground, gameplayBackground, player.texture, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, playerShotSound, EGBackground);
	}
}

namespace resources
{
	void loadResources(Texture& MMBackground, Texture& gameplayBackground, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShotSound, Texture& EGBackground)
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
		EGBackground = LoadTexture("res/textures/end_game/background.png");

		playerTexture = LoadTexture("res/textures/gameplay/player.png");
		
		smallEnemy = LoadTexture("res/textures/gameplay/virus_small.png");
		mediumEnemy = LoadTextureFromImage(mediumEnemyImage);
		bigEnemy = LoadTextureFromImage(bigEnemyImage);
		
		tutorialLeft = LoadTexture("res/textures/gameplay/left_click_tutorial.png");
		tutorialRight = LoadTexture("res/textures/gameplay/right_click_tutorial.png");

		areAssetsReady = true;

		UnloadImage(MMBackroundImage);
	}

	void unloadResources(Font& font, Texture& MMBackground, Texture& gameplayBackground, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShot, Texture& EGBackground)
	{
		// Font
		UnloadFont(font);

		// Sounds
		UnloadSound(playerShot);

		// Textures
		UnloadTexture(MMBackground);
		UnloadTexture(gameplayBackground);
		UnloadTexture(EGBackground);

		UnloadTexture(playerTexture);
		
		UnloadTexture(smallEnemy);
		UnloadTexture(mediumEnemy);
		UnloadTexture(bigEnemy);
		
		UnloadTexture(tutorialLeft);
		UnloadTexture(tutorialRight);
	}
}