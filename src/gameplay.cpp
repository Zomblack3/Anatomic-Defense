#include "gameplay.h"

#include <iostream>

#include "settings.h"

bool isPauseOn = false;

namespace mainFunctions
{
	void gameplay(Player& player, std::vector <Enemy>& enemies, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Font font, Texture& background, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy, Texture tutorialLeft, Texture tutorialRight, Texture hudTexture, Texture hudValuesTexture)
	{
		float deltaTime = GetFrameTime();

		gameplayFunctions::update(player, enemies, deltaTime, buttons, amountOfButtons, currentScreen, smallEnemy, mediumEnemy, bigEnemy);

		gameplayFunctions::draw(player, enemies, buttons, amountOfButtons, font, background, tutorialLeft, tutorialRight, hudTexture, hudValuesTexture);
	}
}

namespace gameplayFunctions
{
	void update(Player& player, std::vector <Enemy>& enemies, float deltaTime, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy)
	{
		if (!isPauseOn && player.isActive)
		{
			enemiesFeatures::spawnEnemy(enemies, smallEnemy, mediumEnemy, bigEnemy, deltaTime);

			playerFeatures::movePlayer(player, deltaTime);
			playerFeatures::rotatePlayer(player);
			playerFeatures::setPlayerDirection(player);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE))
				playerShooting::shootBullet(player, player.bullets, maxAmountOfBullets);

			playerShooting::moveBullet(player.bullets, maxAmountOfBullets, deltaTime);

			if (enemies.size() > 0)
			{
				enemiesFeatures::moveEnemy(enemies, deltaTime);
				enemiesFeatures::checkBulletEnemyCollition(enemies, player, smallEnemy, mediumEnemy);
				enemiesFeatures::checkPlayerEnemyCollition(enemies, player, deltaTime, smallEnemy, mediumEnemy);
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

		float lifePosX = 800.0f;
		float scorePosX = 150.0f;
		int textPositionY = 15;

		std::string scoreText = TextFormat("Puntaje: %i", player.score);
		std::string lifesText = TextFormat("Vidas: %i", player.lifes);

		std::string pauseText = "PAUSA";

		std::string tutorialPauseText = "Presione P para pausar";
		std::string tutorialRightText = "MOVERSE";
		std::string tutorialLeftText = "DISPARAR";
		std::string startingText = "Presione ENTER para iniciar";

		Vector2 pauseTextLength = MeasureTextEx(font, pauseText.c_str(), tutorialTextSize, textSpacing);

		Vector2 scoreTextLength = MeasureTextEx(font, scoreText.c_str(), normalTextSize, textSpacing);
		Vector2 lifesTextLength = MeasureTextEx(font, lifesText.c_str(), normalTextSize, textSpacing);

		Vector2 tutorialPauseTextLength = MeasureTextEx(font, tutorialPauseText.c_str(), tutorialTextSize, textSpacing);
		Vector2 tutorialRightTextLength = MeasureTextEx(font, tutorialRightText.c_str(), tutorialTextSize, textSpacing);
		Vector2 tutorialLeftTextLength = MeasureTextEx(font, tutorialLeftText.c_str(), tutorialTextSize, textSpacing);
		Vector2 startingTextLength = MeasureTextEx(font, startingText.c_str(), tutorialTextSize, textSpacing);

		Vector2 pauseTextPos = { (screenWidth / 2.0f) - (pauseTextLength.x / 2.0f), screenHeight / 4.0f };

		Vector2 scorePos = { scorePosX, static_cast <float> (textPositionY) };
		Vector2 lifesPos = { lifePosX, static_cast <float> (textPositionY) };

		Vector2 tutorialRightTexturePos = { (screenWidth / 4.0f) - (tutorialLeft.width / 2.0f), screenHeight / 4.0f };
		Vector2 tutorialLeftTexturePos = { (screenWidth - (screenWidth / 4.0f)) - (tutorialLeft.width / 2.0f), screenHeight / 4.0f };
		Vector2 startingTextPos = { (screenWidth / 2.0f) - (startingTextLength.x / 2.0f), screenWidth - (screenWidth / 2.0f) };

		Vector2 tutorialPauseTextPos = { (screenWidth / 2.0f) - (tutorialPauseTextLength.x / 2.0f), screenHeight / 6.0f };
		Vector2 tutorialRightTextPos = { tutorialRightTexturePos.x - 5.0f , (screenWidth / 4.0f) + tutorialLeft.height - (tutorialLeft.height / 2.0f)};
		Vector2 tutorialLeftTextPos = { tutorialLeftTexturePos.x - 5.0f, (screenWidth / 4.0f) + tutorialLeft.height - (tutorialLeft.height / 2.0f)};

		int scoreTexturePosX = static_cast <int> (scorePos.x) - 20;
		int scoreTexturePosY = static_cast <int> (scorePos.y) - 5;

		int lifesTexturePosX = static_cast <int> (lifesPos.x) - 20;
		int lifesTexturePosY = static_cast <int> (lifesPos.y) - 5;

		Vector2 origin = { 0.0f, 0.0f };

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
			DrawTextEx(font, tutorialLeftText.c_str(), tutorialLeftTextPos, tutorialTextSize, textSpacing, YELLOW);
			DrawTextEx(font, tutorialRightText.c_str(), tutorialRightTextPos, tutorialTextSize, textSpacing, YELLOW);

			DrawTextEx(font, startingText.c_str(), startingTextPos, tutorialTextSize, textSpacing, YELLOW);
		}
		else
		{
			playerFeatures::drawPlayer(player);

			DrawTexture(hudTexture, 0, 0, WHITE);

			hudValuesTexture.width = static_cast <int> (scoreTextLength.x) + 40;
			hudValuesTexture.height = static_cast <int> (scoreTextLength.y) + 10;

			DrawTexture(hudValuesTexture, scoreTexturePosX, scoreTexturePosY, WHITE);

			hudValuesTexture.width = static_cast <int> (lifesTextLength.x) + 40;
			hudValuesTexture.height = static_cast <int> (lifesTextLength.y) + 10;

			DrawTexture(hudValuesTexture, lifesTexturePosX, lifesTexturePosY, WHITE);

			DrawTextPro(font, scoreText.c_str(), scorePos, origin, 0.0f, normalTextSize, textSpacing, YELLOW);
			DrawTextPro(font, lifesText.c_str(), lifesPos, origin, 0.0f, normalTextSize, textSpacing, YELLOW);
		}

		if (isPauseOn)
		{
			DrawTextEx(font, pauseText.c_str(), pauseTextPos, tutorialTextSize, textSpacing, YELLOW);

			buttonsFeatures::drawButtons(buttons, amountOfButtons, font);
		}

		EndDrawing();
	}
}