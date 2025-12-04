#include "game.h"

#include <math.h>

#include "settings.h"

#include "menu.h"
#include "gameplay.h"
#include "endGame.h"

bool areAssetsReady = false;

namespace run
{
	void game()
	{
		InitWindow(screenWidth, screenHeight, "Anatomic Defense");

		InitAudioDevice();

		const int amountOfButtonsMenu = 3;
		const int amountOfButtonsPause = 2;
		const int amountOfButtonsEG = 2;
		const int amountOfButtonsExit = 2;

		Font baseFont = LoadFont("res/fonts/ds_digital/DS-DIGIB.TTF");
		Font titleFont = LoadFont("res/fonts/Roboto/Roboto-Black.ttf");

		titleFont.baseSize = static_cast <int> (titleTextSize);

		Texture oldScreenTexture = LoadTexture("res/textures/screen_texture.jpg");
		Texture metalTexture = LoadTexture("res/textures/metal_texture.jpg");

		std::string textsOfMenu[amountOfButtonsMenu] = { "INICIAR", "CREDITOS", "SALIR" };
		std::string textsOfPause[amountOfButtonsPause] = { "VOLVER A LA PARTIDA", "VOLVER AL MENU" };
		std::string textsOfEG[amountOfButtonsEG] = { "REINICIAR", "VOLVER AL MENU" };
		std::string textsOfExit[amountOfButtonsExit] = { "SI", "NO" };

		Button buttonsMenu[amountOfButtonsMenu] = { };
		Button buttonsPause[amountOfButtonsPause] = { };
		Button buttonsEG[amountOfButtonsEG] = { };
		Button buttonsExit[amountOfButtonsExit] = { };

		Vector2 buttonsStartingPosMenu = { screenWidth - (screenWidth / 4.0f), (screenHeight / 2.0f) - 100.0f };
		Vector2 buttonsStartingPosOptions = { screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 100.0f };
		Vector2 buttonsStartingPosPause = { screenWidth / 2.0f, (screenHeight / 2.0f) - 50.0f };
		Vector2 buttonsStartingPosEG = { screenWidth / 2.0f, screenHeight / 2.0f + (screenHeight / 8.0f) };
		Vector2 buttonsStartingPosExit = { screenWidth - (screenWidth / 2.0f), (screenHeight / 2.0f) - 50.0f };

		buttonsFeatures::setButtons(buttonsMenu, amountOfButtonsMenu, buttonsStartingPosMenu.x, buttonsStartingPosMenu.y, textsOfMenu, SCREEN::MENU, oldScreenTexture, metalTexture);
		buttonsFeatures::setButtons(buttonsPause, amountOfButtonsPause, buttonsStartingPosPause.x, buttonsStartingPosPause.y, textsOfPause, SCREEN::GAMEPLAY, oldScreenTexture, metalTexture);
		buttonsFeatures::setButtons(buttonsEG, amountOfButtonsEG, buttonsStartingPosEG.x, buttonsStartingPosEG.y, textsOfEG, SCREEN::END_GAME, oldScreenTexture, metalTexture);
		buttonsFeatures::setButtons(buttonsExit, amountOfButtonsExit, buttonsStartingPosExit.x, buttonsStartingPosExit.y, textsOfExit, SCREEN::EXIT, oldScreenTexture, metalTexture);

		metalTexture.width = hudWidth;
		metalTexture.height = hudHeight;

		SCREEN currentScreen = SCREEN::MENU;

		Texture menuBackground = { };
		Texture gameplayBackground = { };
		Texture EGBackground = { };

		Texture smallEnemy = { };
		Texture mediumEnemy = { };
		Texture bigEnemy = { };

		Texture tutorialLeft = { };
		Texture tutorialRight = { };

		Sound playerShotSound = { };
		Sound smallEnemyDeathSound = { };
		Sound mediumEnemyDeathSound = { };
		Sound bigEnemyDeathSound = { };

		Player player;

		playerFeatures::setDefault(player);

		std::vector <Enemy> enemies = { };

		resources::loadResources(menuBackground, gameplayBackground, player.texture, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, player.shotSound, EGBackground, smallEnemyDeathSound, mediumEnemyDeathSound, bigEnemyDeathSound);

		while (!WindowShouldClose())
		{
			switch (currentScreen)
			{
			case SCREEN::MENU:

				mainFunctions::menu(currentScreen, buttonsMenu, amountOfButtonsMenu, menuBackground, titleFont, baseFont);

				break;
			case SCREEN::GAMEPLAY:

				mainFunctions::gameplay(player, enemies, buttonsPause, amountOfButtonsPause, currentScreen, baseFont, gameplayBackground, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, metalTexture, oldScreenTexture, smallEnemyDeathSound, mediumEnemyDeathSound, bigEnemyDeathSound);

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

		resources::unloadResources(baseFont, menuBackground, gameplayBackground, player.texture, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, playerShotSound, EGBackground, smallEnemyDeathSound, mediumEnemyDeathSound, bigEnemyDeathSound);
	}
}

namespace resources
{
	void loadResources(Texture& menuBackground, Texture& gameplayBackground, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShotSound, Texture& EGBackground, Sound& smallEnemyDeathSound, Sound& mediumEnemyDeathSound, Sound& bigEnemyDeathSound)
	{
		const int sizeOfMediumEnemy = 50;
		const int sizeOfBigEnemy = 120;

		// Sounds

		/* Player */
		playerShotSound = LoadSound("res/sound_efects/player/player_shot.wav");

		/* Enemies */
		smallEnemyDeathSound = LoadSound("res/sound_efects/enemies/small_enemy_death_sound.wav");
		mediumEnemyDeathSound = LoadSound("res/sound_efects/enemies/medium_enemy_death_sound.wav");
		bigEnemyDeathSound = LoadSound("res/sound_efects/enemies/big_enemy_death_sound.wav");

		// Textures
		
		/* Backgrounds */
		menuBackground = LoadTexture("res/textures/main_menu/background.png");
		menuBackground.width = screenWidth;
		menuBackground.height = screenHeight;

		gameplayBackground = LoadTexture("res/textures/gameplay/background.png");
		EGBackground = LoadTexture("res/textures/end_game/background.png");

		/* Player */
		playerTexture = LoadTexture("res/textures/gameplay/player.png");
		
		/* Enemy */
		smallEnemy = LoadTexture("res/textures/gameplay/virus_small.png");
		
		mediumEnemy = LoadTexture("res/textures/gameplay/virus_medium.png");
		mediumEnemy.width = sizeOfMediumEnemy;
		mediumEnemy.height = sizeOfMediumEnemy;

		bigEnemy = LoadTexture("res/textures/gameplay/virus_big.png");
		bigEnemy.width = sizeOfBigEnemy;
		bigEnemy.height = sizeOfBigEnemy;
		
		/* Tutorial */
		tutorialLeft = LoadTexture("res/textures/gameplay/left_click_tutorial.png");
		tutorialRight = LoadTexture("res/textures/gameplay/right_click_tutorial.png");

		areAssetsReady = true;
	}

	void unloadResources(Font& font, Texture& MMBackground, Texture& gameplayBackground, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShot, Texture& EGBackground, Sound& smallEnemyDeathSound, Sound& mediumEnemyDeathSound, Sound& bigEnemyDeathSound)
	{
		// Font
		UnloadFont(font);

		// Sounds
		UnloadSound(playerShot);
		UnloadSound(smallEnemyDeathSound);
		UnloadSound(mediumEnemyDeathSound);
		UnloadSound(bigEnemyDeathSound);

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