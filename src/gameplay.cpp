#include "gameplay.h"

#include <iostream>

#include "settings.h"

bool isPauseOn = false;

namespace mainFunctions
{
	void gameplay(Player& player, std::vector <Enemy>& enemies, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Font font, Texture& background, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy, Texture tutorialLeft, Texture tutorialRight)
	{
		float deltaTime = GetFrameTime();

		gameplayFunctions::update(player, enemies, deltaTime, buttons, amountOfButtons, currentScreen, smallEnemy, mediumEnemy, bigEnemy);

		gameplayFunctions::draw(player, enemies, buttons, amountOfButtons, font, background, tutorialLeft, tutorialRight);
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
			{
				playerFeatures::setDefault(player);

				currentScreen = SCREEN::END_SCREEN;
			}
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
							currentScreen = buttons[i].directionScreen;
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

	void draw(Player player, std::vector <Enemy> enemies, Button buttons[], int amountOfButtons, Font font, Texture background, Texture tutorialLeft, Texture tutorialRight)
	{
		//int lifePositionX = 800;
		int textPositionY = 20;

		Vector2 scorePos = { 50.0f, static_cast <float> (textPositionY) };
		Vector2 lifesPos = { 800.0f, static_cast <float> (textPositionY) };
		Vector2 origin = { 0.0f, 0.0f };

		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(background, 0, 0, WHITE);

		playerShooting::drawBullets(player.bullets, maxAmountOfBullets);

		playerFeatures::drawPlayer(player);

		enemiesFeatures::drawEnemy(enemies);

		DrawRectangle(0, 0, screenWidth, 50, WHITE);

		DrawTextPro(font, TextFormat("Score: %i", player.score), scorePos, origin, 0.0f, normalTextSize, 2.0f, BLACK);
		DrawTextPro(font, "Vida: ", lifesPos, origin, 0.0f, normalTextSize, 2.0f, BLACK);
		DrawRectangle(static_cast<int>(lifesPos.x) + 50, textPositionY, player.lives * 50, 20, RED);

		if (isPauseOn)
			buttonsFeatures::drawButtons(buttons, amountOfButtons, font);

		if (!player.isActive)
		{
			DrawTexture(tutorialLeft, static_cast <int> ((screenWidth / 4.0f) - (tutorialLeft.width / 2.0f)), static_cast <int> (screenHeight / 4.0f), WHITE);
			DrawTexture(tutorialRight, static_cast <int> ((screenWidth - (screenWidth / 4.0f)) - (tutorialLeft.width / 2.0f)), static_cast <int> (screenHeight / 4.0f), WHITE);

			DrawText("DISPARAR", static_cast <int> (((screenWidth / 4.0f) - (tutorialLeft.width / 2.0f)) - (MeasureText("DISPARAR", 40) / 5.0f)), static_cast <int> ((screenWidth / 4.0f) + tutorialLeft.height - (tutorialLeft.height / 2.0f)), 40, WHITE);
			DrawText("MOVERSE", static_cast <int> ((screenWidth - (screenWidth / 4.0f)) - (tutorialRight.width / 2.0f) - (MeasureText("MOVERSE", 40) / 5.0f)), static_cast <int> ((screenWidth / 4.0f) + tutorialRight.height - (tutorialRight.height / 2.0f)), 40, WHITE);

			DrawText("Presione ENTER para iniciar", static_cast <int> ((screenWidth / 2.0f) - (MeasureText("Presione ENTER para iniciar", 40) / 2.0f)), static_cast <int> (screenWidth - (screenWidth / 2.0f)), 40, WHITE);
		}

		EndDrawing();
	}
}