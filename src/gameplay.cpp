#include "gameplay.h"

#include <iostream>

#include "settings.h"

bool isPauseOn = false;

namespace gameplay
{
	void gameplay(Player& player, std::vector <Enemy>& enemies, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Font font, Image background)
	{
		float deltaTime = GetFrameTime();

		gameplayFeatures::update(player, enemies, deltaTime, buttons, amountOfButtons, currentScreen);

		gameplayFeatures::draw(player, enemies, buttons, amountOfButtons, font, background);
	}
}

namespace gameplayFeatures
{
	void update(Player& player, std::vector <Enemy>& enemies, float deltaTime, Button buttons[], int amountOfButtons, SCREEN& currentScreen)
	{
		if (!isPauseOn)
		{
			enemiesFeatures::spawnEnemy(enemies, deltaTime);

			playerFeatures::movePlayer(player, deltaTime);
			playerFeatures::rotatePlayer(player);
			playerFeatures::setPlayerDirection(player);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE))
				playerShooting::shootBullet(player, player.bullets, maxAmountOfBullets);

			playerShooting::moveBullet(player.bullets, maxAmountOfBullets, deltaTime);

			if (enemies.size() > 0)
			{
				enemiesFeatures::moveEnemy(enemies, deltaTime);
				enemiesFeatures::checkBulletEnemyCollition(enemies, player);
				enemiesFeatures::checkPlayerEnemyCollition(enemies, player, deltaTime);
			}

			if (IsKeyPressed(KEY_P))
				isPauseOn = true;

			if (!playerFeatures::isAlive(player))
			{
				playerFeatures::setDefault(player);

				currentScreen = SCREEN::END_SCREEN;
			}
		}
		else
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
	}

	void draw(Player player, std::vector <Enemy> enemies, Button buttons[], int amountOfButtons, Font font, Image background)
	{
		int lifePositionX = 800;
		int textPositionY = 20;

		Vector2 scorePos = { 50.0f, static_cast <float> (textPositionY) };
		Vector2 scoreOrigin = { 0.0f, 0.0f };

		BeginDrawing();

		ClearBackground(WHITE);

		playerFeatures::drawPlayer(player);

		playerShooting::drawBullets(player.bullets, maxAmountOfBullets);

		enemiesFeatures::drawEnemy(enemies);

		DrawRectangle(0, 0, screenWidth, 50, WHITE);

		//DrawText(TextFormat("Score: %i", player.score), 50, textPositionY, 20, BLACK);
		DrawTextPro(font, TextFormat("Score: %i", player.score), scorePos, scoreOrigin, 0.0f, 20.0f, 2.0f, BLACK);
		DrawText("Vida: ", lifePositionX, textPositionY, 20, BLACK);
		DrawRectangle(lifePositionX + 50, textPositionY, player.lives * 50, 20, RED);

		DrawLine(static_cast <int> (player.textureDest.x), static_cast <int> (player.textureDest.y), GetMouseX(), GetMouseY(), YELLOW);

		if (isPauseOn)
			buttonsFeatures::drawButtons(buttons, amountOfButtons);

		EndDrawing();
	}
}