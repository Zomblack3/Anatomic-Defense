#include "game.h"

#include "menu.h"
#include "gameplay.h"
#include "endGame.h"
#include "credits.h"

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

		Music menuMusic = { };
		Music gameplayMusic = { };

		Sound playerShotSound = { };
		Sound playerHitSound = { };

		Sound smallEnemyDeathSound = { };
		Sound mediumEnemyDeathSound = { };
		Sound bigEnemyDeathSound = { };
		
		resources::loadResources(menuBackground, gameplayBackground, playerTexture, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, playerShotSound, EGBackground, smallEnemyDeathSound, mediumEnemyDeathSound, bigEnemyDeathSound, playerHitSound, baseFont, titleFont, metalTexture, oldScreenTexture, menuMusic, gameplayMusic);

		const int amountOfButtonsMenu = 3;
		const int amountOfButtonsCredits = 5;
		const int amountOfButtonsPause = 2;
		const int amountOfButtonsEG = 2;

		titleFont.baseSize = static_cast <int> (titleTextSize);

		std::string textsOfMenu[amountOfButtonsMenu] = { "INICIAR", "CREDITOS", "SALIR" };
		std::string textsOfCredits[amountOfButtonsCredits] = { "PROGRAMACION", "ARTE", "MUSICA", "SONIDO", "TIPOGRAFIAS" };
		std::string textsOfPause[amountOfButtonsPause] = { "VOLVER A LA PARTIDA", "VOLVER AL MENU" };
		std::string textsOfEG[amountOfButtonsEG] = { "REINICIAR", "VOLVER AL MENU" };

		std::string textOfReturnMenu = "VOLVER AL MENU";
		std::string textOfReturnCredits = "VOLVER A LOS CREDITOS";

		Button buttonsMenu[amountOfButtonsMenu] = { };
		Button buttonsCredits[amountOfButtonsCredits] = { };
		Button buttonsPause[amountOfButtonsPause] = { };
		Button buttonsEG[amountOfButtonsEG] = { };

		Button returnMenuButton = { };
		Button returnCreditsButton = { };

		Vector2 buttonsStartingPosMenu = { screenWidth / 2.0f, (screenHeight / 2.0f) - 100.0f };
		Vector2 buttonsStartingPosCredits = { screenWidth / 2.0f, (screenHeight / 2.0f) - 250.0f };
		Vector2 buttonsStartingPosPause = { screenWidth / 2.0f, (screenHeight / 2.0f) - 50.0f };
		Vector2 buttonsStartingPosEG = { screenWidth / 2.0f, screenHeight / 2.0f + (screenHeight / 8.0f) };

		Vector2 returnMenuButtonPos = { screenWidth / 2.0f, screenHeight - (screenHeight / 6.0f) };
		Vector2 returnCreditsButtonPos = { screenWidth / 2.0f, screenHeight - (screenHeight / 6.0f) };

		buttonsFeatures::setButtons(buttonsMenu, amountOfButtonsMenu, buttonsStartingPosMenu.x, buttonsStartingPosMenu.y, textsOfMenu, SCREEN::MENU, oldScreenTexture, metalTexture, baseFont);
		buttonsFeatures::setButtons(buttonsCredits, amountOfButtonsCredits, buttonsStartingPosCredits.x, buttonsStartingPosCredits.y, textsOfCredits, SCREEN::CREDITS, oldScreenTexture, metalTexture, baseFont);
		buttonsFeatures::setButtons(buttonsPause, amountOfButtonsPause, buttonsStartingPosPause.x, buttonsStartingPosPause.y, textsOfPause, SCREEN::GAMEPLAY, oldScreenTexture, metalTexture, baseFont);
		buttonsFeatures::setButtons(buttonsEG, amountOfButtonsEG, buttonsStartingPosEG.x, buttonsStartingPosEG.y, textsOfEG, SCREEN::END_GAME, oldScreenTexture, metalTexture, baseFont);

		buttonsFeatures::setSingleButton(returnMenuButton, returnMenuButtonPos.x, returnMenuButtonPos.y, textOfReturnMenu, SCREEN::MENU, oldScreenTexture, metalTexture, baseFont);
		buttonsFeatures::setSingleButton(returnCreditsButton, returnCreditsButtonPos.x, returnCreditsButtonPos.y, textOfReturnCredits, SCREEN::CREDITS, oldScreenTexture, metalTexture, baseFont);

		metalTexture.width = hudWidth;
		metalTexture.height = hudHeight;

		SetMusicVolume(gameplayMusic, 0.5);

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

				if (!IsMusicStreamPlaying(menuMusic))
					PlayMusicStream(menuMusic);
				else
					UpdateMusicStream(menuMusic);

				mainFunctions::menu(currentScreen, buttonsMenu, amountOfButtonsMenu, menuBackground, titleFont, baseFont);

				if (currentScreen != SCREEN::MENU && currentScreen != SCREEN::CREDITS)
					StopMusicStream(menuMusic);

				break;
			case SCREEN::GAMEPLAY:

				if (!IsMusicStreamPlaying(gameplayMusic))
					PlayMusicStream(gameplayMusic);
				else
					UpdateMusicStream(gameplayMusic);

				mainFunctions::gameplay(player, enemies, buttonsPause, amountOfButtonsPause, currentScreen, baseFont, gameplayBackground, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, metalTexture, oldScreenTexture, smallEnemyDeathSound, mediumEnemyDeathSound, bigEnemyDeathSound);

				break;
			case SCREEN::END_GAME:

				mainFunctions::endGame(player, enemies, buttonsEG, amountOfButtonsEG, currentScreen, titleFont, baseFont, EGBackground);

				break;
			case SCREEN::CREDITS:
			case SCREEN::CREDITS_PROGRAMMERS:
			case SCREEN::CREDITS_ARTISTS:
			case SCREEN::CREDITS_MUSICIANS:
			case SCREEN::CREDITS_SOUND_ENGENNIERS:
			case SCREEN::CREDITS_FONTS:

				if (!IsMusicStreamPlaying(menuMusic))
					PlayMusicStream(menuMusic);
				else
					UpdateMusicStream(menuMusic);

				mainFunctions::credits(currentScreen, returnMenuButton, returnCreditsButton, buttonsCredits, amountOfButtonsCredits, metalTexture, oldScreenTexture, metalTexture, baseFont);

				break;
			case SCREEN::EXIT:

				CloseAudioDevice();

				CloseWindow();

				break;
			default:
				break;
			}
		}

		resources::unloadResources(baseFont, menuBackground, gameplayBackground, player.texture, smallEnemy, mediumEnemy, bigEnemy, tutorialLeft, tutorialRight, playerShotSound, EGBackground, smallEnemyDeathSound, mediumEnemyDeathSound, bigEnemyDeathSound, titleFont, metalTexture, oldScreenTexture, playerHitSound, menuMusic, gameplayMusic);
	}
}

namespace resources
{
	void loadResources(Texture& menuBackground, Texture& gameplayBackground, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShotSound, Texture& EGBackground, Sound& smallEnemyDeathSound, Sound& mediumEnemyDeathSound, Sound& bigEnemyDeathSound, Sound& playerHitSound, Font& baseFont, Font& titleFont, Texture& metalTexture, Texture& oldScreenTexture, Music& menuMusic, Music& gameplayMusic)
	{
		// Fonts // 
		
		baseFont = LoadFont("res/fonts/ds_digital/DS-DIGIB.TTF");
		titleFont = LoadFont("res/fonts/Roboto/Roboto-Black.ttf");

		// Music //

		menuMusic = LoadMusicStream("res/music/menu_music.mp3");
		gameplayMusic = LoadMusicStream("res/music/gameplay_music.mp3");

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
		oldScreenTexture = LoadTexture("res/textures/old_screen_texture.jpg");

		/* Backgrounds */
		menuBackground = LoadTexture("res/textures/main_menu/background.png");
		menuBackground.width = screenWidth;
		menuBackground.height = screenHeight;

		gameplayBackground = LoadTexture("res/textures/gameplay/background.png");
		EGBackground = LoadTexture("res/textures/end_game/background.jpg");

		/* Player */
		playerTexture = LoadTexture("res/textures/gameplay/player.png");
		
		/* Enemy */
		smallEnemy = LoadTexture("res/textures/gameplay/small_enemy.png");
		mediumEnemy = LoadTexture("res/textures/gameplay/medium_enemy.png");
		bigEnemy = LoadTexture("res/textures/gameplay/big_enemy.png");
		
		/* Tutorial */
		tutorialLeft = LoadTexture("res/textures/gameplay/left_click_tutorial.png");
		tutorialRight = LoadTexture("res/textures/gameplay/right_click_tutorial.png");
	}

	void unloadResources(Font& baseFont, Texture& MMBackground, Texture& gameplayBackground, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShotSound, Texture& EGBackground, Sound& smallEnemyDeathSound, Sound& mediumEnemyDeathSound, Sound& bigEnemyDeathSound, Font& titleFont, Texture& metalTexture, Texture& screenTexture, Sound& playerHitSound, Music& menuMusic, Music& gameplayMusic)
	{
		// Font //
		UnloadFont(baseFont);
		UnloadFont(titleFont);

		// Music //
		UnloadMusicStream(menuMusic);
		UnloadMusicStream(gameplayMusic);

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