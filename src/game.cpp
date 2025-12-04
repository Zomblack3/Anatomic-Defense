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

		SCREEN currentScreen = SCREEN::MENU;

		Texture playerTexture = { };

		Texture menuBackground = { };
		Texture gameplayBackground = { };
		Texture EGBackground = { };

		Texture smallEnemy = { };
		Texture mediumEnemy = { };
		Texture bigEnemy = { };

		Texture tutorialLeft = { };
		Texture tutorialRight = { };

		Texture oldScreenTexture = { };
		Texture metalTexture = { };

		Font baseFont = { };
		Font titleFont = { };

		Sound playerShotSound = { };
		Sound playerHitSound = { };

		Sound smallEnemyDeathSound = { };
		Sound mediumEnemyDeathSound = { };
		Sound bigEnemyDeathSound = { };
		
		resources::loadResources(menuBackground, gameplayBackground, playerTexture, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, playerShotSound, EGBackground, smallEnemyDeathSound, mediumEnemyDeathSound, bigEnemyDeathSound, playerHitSound, baseFont, titleFont, metalTexture, oldScreenTexture);

		const int amountOfButtonsMenu = 3;
		const int amountOfButtonsPause = 2;
		const int amountOfButtonsEG = 2;
		const int amountOfButtonsExit = 2;

		titleFont.baseSize = static_cast <int> (titleTextSize);

		std::string textsOfMenu[amountOfButtonsMenu] = { "INICIAR", "CREDITOS", "SALIR" };
		std::string textsOfPause[amountOfButtonsPause] = { "VOLVER A LA PARTIDA", "VOLVER AL MENU" };
		std::string textsOfEG[amountOfButtonsEG] = { "REINICIAR", "VOLVER AL MENU" };
		std::string textsOfExit[amountOfButtonsExit] = { "SI", "NO" };

		Button buttonsMenu[amountOfButtonsMenu] = { };
		Button buttonsPause[amountOfButtonsPause] = { };
		Button buttonsEG[amountOfButtonsEG] = { };
		Button buttonsExit[amountOfButtonsExit] = { };

		Vector2 buttonsStartingPosMenu = { screenWidth / 2.0f, (screenHeight / 2.0f) - 100.0f };
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

		Player player;

		player.texture = playerTexture;
		player.shotSound = playerShotSound;
		player.hitSound = playerHitSound;

		playerFeatures::setDefault(player);

		std::vector <Enemy> enemies = { };

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

		resources::unloadResources(baseFont, menuBackground, gameplayBackground, player.texture, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, playerShotSound, EGBackground, smallEnemyDeathSound, mediumEnemyDeathSound, bigEnemyDeathSound, titleFont, metalTexture, oldScreenTexture, playerHitSound);
	}
}

namespace resources
{
	void loadResources(Texture& menuBackground, Texture& gameplayBackground, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShotSound, Texture& EGBackground, Sound& smallEnemyDeathSound, Sound& mediumEnemyDeathSound, Sound& bigEnemyDeathSound, Sound& playerHitSound, Font& baseFont, Font& titleFont, Texture& metalTexture, Texture& oldScreenTexture)
	{
		const int sizeOfMediumEnemy = 50;
		const int sizeOfBigEnemy = 120;

		// Fonts // 
		
		baseFont = LoadFont("res/fonts/ds_digital/DS-DIGIB.TTF");
		titleFont = LoadFont("res/fonts/Roboto/Roboto-Black.ttf");

		// Sounds //

		/* Player */
		playerShotSound = LoadSound("res/sound_efects/player/player_shot.wav");
		playerHitSound = LoadSound("res/sound_efects/player/hit_sound.mp3");

		/* Enemies */
		smallEnemyDeathSound = LoadSound("res/sound_efects/enemies/small_enemy_death_sound.wav");
		mediumEnemyDeathSound = LoadSound("res/sound_efects/enemies/medium_enemy_death_sound.wav");
		bigEnemyDeathSound = LoadSound("res/sound_efects/enemies/big_enemy_death_sound.wav");

		// Textures //

		/* General */
		metalTexture = LoadTexture("res/textures/metal_texture.jpg");
		oldScreenTexture = LoadTexture("res/textures/screen_texture.jpg");

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

	void unloadResources(Font& baseFont, Texture& MMBackground, Texture& gameplayBackground, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShotSound, Texture& EGBackground, Sound& smallEnemyDeathSound, Sound& mediumEnemyDeathSound, Sound& bigEnemyDeathSound, Font& titleFont, Texture& metalTexture, Texture& screenTexture, Sound& playerHitSound)
	{
		// Font //
		UnloadFont(baseFont);
		UnloadFont(titleFont);

		// Sounds //
		UnloadSound(playerShotSound);
		UnloadSound(playerHitSound);
		UnloadSound(smallEnemyDeathSound);
		UnloadSound(mediumEnemyDeathSound);
		UnloadSound(bigEnemyDeathSound);

		// Textures //
		UnloadTexture(MMBackground);
		UnloadTexture(gameplayBackground);
		UnloadTexture(EGBackground);
		
		UnloadTexture(metalTexture);
		UnloadTexture(screenTexture);

		UnloadTexture(playerTexture);
		
		UnloadTexture(smallEnemy);
		UnloadTexture(mediumEnemy);
		UnloadTexture(bigEnemy);
		
		UnloadTexture(tutorialLeft);
		UnloadTexture(tutorialRight);
	}
}