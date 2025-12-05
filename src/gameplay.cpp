#include "gameplay.h"

bool isPauseOn = false;

namespace mainFunctions
{
	void gameplay(Player& player, std::vector <Enemy>& enemies, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Font font, Texture& background, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy, Texture tutorialLeft, Texture tutorialRight, Texture hudTexture, Texture hudValuesTexture, Sound smallEnemyDeathSound, Sound mediumEnemyDeathSound, Sound bigEnemyDeathSound)
	{
		float deltaTime = GetFrameTime();

		gameplayFunctions::update(player, enemies, deltaTime, buttons, amountOfButtons, currentScreen, smallEnemy, mediumEnemy, bigEnemy, smallEnemyDeathSound, mediumEnemyDeathSound, bigEnemyDeathSound);

		gameplayFunctions::draw(player, enemies, buttons, amountOfButtons, font, background, tutorialLeft, tutorialRight, hudTexture, hudValuesTexture);
	}
}

namespace gameplayFunctions
{
	void update(Player& player, std::vector <Enemy>& enemies, float deltaTime, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy, Sound smallEnemyDeathSound, Sound mediumEnemyDeathSound, Sound bigEnemyDeathSound)
	{
		if (!isPauseOn && player.isActive)
		{
			enemiesFeatures::spawnEnemy(enemies, smallEnemy, mediumEnemy, bigEnemy, deltaTime, smallEnemyDeathSound, mediumEnemyDeathSound, bigEnemyDeathSound);

			playerFeatures::movePlayer(player, deltaTime);

			playerFeatures::rotatePlayer(player);

			playerFeatures::setPlayerDirection(player);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE))
				playerShooting::shootBullet(player, player.bullets, maxAmountOfBullets);

			playerShooting::moveBullet(player.bullets, maxAmountOfBullets, deltaTime);

			if (enemies.size() > 0)
			{
				enemiesFeatures::moveEnemy(enemies, deltaTime);

				enemiesFeatures::checkBulletEnemyCollition(enemies, player, smallEnemy, mediumEnemy, smallEnemyDeathSound, mediumEnemyDeathSound);
				enemiesFeatures::checkPlayerEnemyCollition(enemies, player, deltaTime, smallEnemy, mediumEnemy, smallEnemyDeathSound, mediumEnemyDeathSound);
			}

			if (IsKeyPressed(KEY_P))
				isPauseOn = true;

			if (!playerFeatures::isAlive(player))
				currentScreen = SCREEN::END_GAME;
		}
		else if (isPauseOn)
		{
			for (int i = 0; i < amountOfButtons; i++)
			{
				buttonsFeatures::chageButtonState(buttons[i]);

				if (buttonsFeatures::collitionCheckButtonMouse(buttons[i].rec))
				{
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						if (i == 0)
							isPauseOn = false;
						else
						{
							currentScreen = buttons[i].directionScreen;

							isPauseOn = false;

							playerFeatures::setDefault(player);

							enemies.clear();
						}
					}
				}
			}
		}
		else
		{
			if (IsKeyPressed(KEY_ENTER))
				player.isActive = true;
		}
	}

	void draw(Player player, std::vector <Enemy> enemies, Button buttons[], int amountOfButtons, Font font, Texture background, Texture tutorialLeft, Texture tutorialRight, Texture hudTexture, Texture hudValuesTexture)
	{
		const int tutorialTextSize = 40;
		const int idicationsTextSize = 25;

		float lifePosX = 800.0f;
		float scorePosX = 150.0f;
		int textPositionY = 15;

		// Texts //
		
		/* Player variables */
		std::string scoreText = TextFormat("Puntaje: %i", player.score);
		std::string lifesText = TextFormat("Vidas: %i", player.lifes);

		/* Pause title */
		std::string pauseText = "PAUSA";

		/* Tutorial */
		std::string tutorialPauseText = "Presione P para pausar";
		std::string tutorialRightText = "MOVERSE";
		std::string tutorialLeftText = "DISPARAR";
		std::string tutorialIndications1Text = "Tu objetivo es eliminar la mayor cantidad de viruses";
		std::string tutorialIndications2Text = "Si chocas contra un virus, perdes una vida";
		std::string tutorialLoseConditionText = "Si te quedas sin vidas, el paciente muere";
		std::string startingText = "Presione ENTER para iniciar";

		// Texts length //

		/* Player variables */
		Vector2 scoreTextLength = MeasureTextEx(font, scoreText.c_str(), normalTextSize, textSpacing);
		Vector2 lifesTextLength = MeasureTextEx(font, lifesText.c_str(), normalTextSize, textSpacing);

		/* Pause */
		Vector2 pauseTextLength = MeasureTextEx(font, pauseText.c_str(), tutorialTextSize, textSpacing);

		/* Tutorial */
		Vector2 tutorialPauseTextLength = MeasureTextEx(font, tutorialPauseText.c_str(), tutorialTextSize, textSpacing);
		Vector2 tutorialRightTextLength = MeasureTextEx(font, tutorialRightText.c_str(), tutorialTextSize, textSpacing);
		Vector2 tutorialLeftTextLength = MeasureTextEx(font, tutorialLeftText.c_str(), tutorialTextSize, textSpacing);
		Vector2 tutorialIndications1TextLength = MeasureTextEx(font, tutorialIndications1Text.c_str(), idicationsTextSize, textSpacing);
		Vector2 tutorialIndications2TextLength = MeasureTextEx(font, tutorialIndications2Text.c_str(), idicationsTextSize, textSpacing);
		Vector2 tutorialLoseConditionTextLength = MeasureTextEx(font, tutorialLoseConditionText.c_str(), idicationsTextSize, textSpacing);
		Vector2 startingTextLength = MeasureTextEx(font, startingText.c_str(), tutorialTextSize, textSpacing);

		// Tutorial texture positions //

		Vector2 tutorialRightTexturePos = { (screenWidth / 4.0f) - (tutorialLeft.width / 2.0f), screenHeight / 4.0f };
		Vector2 tutorialLeftTexturePos = { (screenWidth - (screenWidth / 4.0f)) - (tutorialLeft.width / 2.0f), screenHeight / 4.0f };
		
		// Texts positions //

		/* Player variables */
		Vector2 scorePos = { scorePosX, static_cast <float> (textPositionY) };
		Vector2 lifesPos = { lifePosX, static_cast <float> (textPositionY) };

		int extraDistanceX = 20;
		int extraDistanceY = 5;

		int scoreTexturePosX = static_cast <int> (scorePos.x) - extraDistanceX;
		int scoreTexturePosY = static_cast <int> (scorePos.y) - extraDistanceY;

		int lifesTexturePosX = static_cast <int> (lifesPos.x) - extraDistanceX;
		int lifesTexturePosY = static_cast <int> (lifesPos.y) - extraDistanceY;

		/* Pause */
		Vector2 pauseTextPos = { (screenWidth / 2.0f) - (pauseTextLength.x / 2.0f), screenHeight / 4.0f };

		/* Tutorial */
		Vector2 tutorialPauseTextPos = { (screenWidth / 2.0f) - (tutorialPauseTextLength.x / 2.0f), screenHeight / 6.0f };
		Vector2 tutorialRightTextPos = { tutorialRightTexturePos.x - 5.0f , (screenWidth / 4.0f) + tutorialLeft.height - (tutorialLeft.height / 2.0f)};
		Vector2 tutorialLeftTextPos = { tutorialLeftTexturePos.x - 5.0f, (screenWidth / 4.0f) + tutorialLeft.height - (tutorialLeft.height / 2.0f)};
		Vector2 tutorialIndications1TextPos = { (screenWidth / 2.0f) - (tutorialIndications1TextLength.x / 2.0f), (screenHeight / 2.0f) + 100.0f };
		Vector2 tutorialIndications2TextPos = { (screenWidth / 2.0f) - (tutorialIndications2TextLength.x / 2.0f), (screenHeight / 2.0f) + 150.0f };
		Vector2 tutorialLoseConditionsTextPos = { (screenWidth / 2.0f) - (tutorialLoseConditionTextLength.x / 2.0f), (screenHeight / 2.0f) + 200.0f };
		Vector2 startingTextPos = { (screenWidth / 2.0f) - (startingTextLength.x / 2.0f), screenHeight - (screenHeight / 6.0f) };

		// HUD sizes //

		const int hudExtraWidth = 40;
		const int hudExtraHeight = 10;

		int hudValuesTextureScoreWidth = static_cast <int> (scoreTextLength.x) + hudExtraWidth;
		int hudValuesTextureScoreHeight = static_cast <int> (scoreTextLength.y) + hudExtraHeight;

		int hudValuesTextureLifesWidth = static_cast <int> (lifesTextLength.x) + hudExtraWidth;
		int hudValuesTextureLifesHeight = static_cast <int> (lifesTextLength.y) + hudExtraHeight;

		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(background, 0, 0, WHITE);

		playerShooting::drawBullets(player.bullets, maxAmountOfBullets);

		enemiesFeatures::drawEnemy(enemies);

		if (!player.isActive)
		{
			DrawTexture(tutorialRight, static_cast <int> (tutorialRightTexturePos.x), static_cast <int> (tutorialRightTexturePos.y), WHITE);
			DrawTexture(tutorialLeft, static_cast <int> (tutorialLeftTexturePos.x), static_cast <int> (tutorialLeftTexturePos.y), WHITE);

			DrawTextEx(font, tutorialPauseText.c_str(), tutorialPauseTextPos, tutorialTextSize, textSpacing, YELLOW);
			DrawTextEx(font, tutorialRightText.c_str(), tutorialRightTextPos, tutorialTextSize, textSpacing, YELLOW);
			DrawTextEx(font, tutorialLeftText.c_str(), tutorialLeftTextPos, tutorialTextSize, textSpacing, YELLOW);
			DrawTextEx(font, tutorialIndications1Text.c_str(), tutorialIndications1TextPos, idicationsTextSize, textSpacing, YELLOW);
			DrawTextEx(font, tutorialIndications2Text.c_str(), tutorialIndications2TextPos, idicationsTextSize, textSpacing, YELLOW);
			DrawTextEx(font, tutorialLoseConditionText.c_str(), tutorialLoseConditionsTextPos, idicationsTextSize, textSpacing, YELLOW);

			DrawTextEx(font, startingText.c_str(), startingTextPos, tutorialTextSize, textSpacing, YELLOW);
		}
		else
		{
			playerFeatures::drawPlayer(player);

			DrawTexture(hudTexture, 0, 0, WHITE);

			hudValuesTexture.width = hudValuesTextureScoreWidth;
			hudValuesTexture.height = hudValuesTextureScoreHeight;

			DrawTexture(hudValuesTexture, scoreTexturePosX, scoreTexturePosY, WHITE);

			hudValuesTexture.width = hudValuesTextureLifesWidth;
			hudValuesTexture.height = hudValuesTextureLifesHeight;

			DrawTexture(hudValuesTexture, lifesTexturePosX, lifesTexturePosY, WHITE);

			DrawTextEx(font, scoreText.c_str(), scorePos, normalTextSize, textSpacing, YELLOW);
			DrawTextEx(font, lifesText.c_str(), lifesPos, normalTextSize, textSpacing, YELLOW);
		}

		if (isPauseOn)
		{
			DrawTextEx(font, pauseText.c_str(), pauseTextPos, tutorialTextSize, textSpacing, YELLOW);

			buttonsFeatures::drawButtons(buttons, amountOfButtons, font);
		}

		EndDrawing();
	}
}