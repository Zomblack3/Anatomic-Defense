#include "gameplay.h"

#include <iostream>

#include "settings.h"

bool isPauseOn = false;

namespace gameplay
{
	void gameplay(Player& player, std::vector <Enemy>& enemies, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Font font, Image& backgroundAnim, Texture& background, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy, int frames, Texture tutorialLeft, Texture tutorialRight)
	{
		float deltaTime = GetFrameTime();

		gameplayFeatures::update(player, enemies, deltaTime, buttons, amountOfButtons, currentScreen, background, backgroundAnim, frames, smallEnemy, mediumEnemy, bigEnemy);

		gameplayFeatures::draw(player, enemies, buttons, amountOfButtons, font, background, tutorialLeft, tutorialRight);
	}
}

namespace gameplayFeatures
{
	unsigned int nextFrameDataOffset = 0;  // Current byte offset to next frame in image.data

	int currentAnimFrame = 0;       // Current animation frame to load and draw
	float frameDelay = 1.0f / 15.0f;             // Frame delay to switch between animation frames
	float animTimer = 0.0f;           // General frames counter

	void update(Player& player, std::vector <Enemy>& enemies, float deltaTime, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Texture& gameplayBackground, Image& backgroundAnim, int frames, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy)
	{
		if (!isPauseOn && player.isActive)
		{
			updateBackground(backgroundAnim, gameplayBackground, frames, deltaTime);

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
		int lifePositionX = 800;
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

		DrawTextPro(font, TextFormat("Score: %i", player.score), scorePos, origin, 0.0f, 20.0f, 2.0f, BLACK);
		DrawTextPro(font, "Vida: ", lifesPos, origin, 0.0f, 20.0f, 2.0f, BLACK);
		DrawRectangle(lifePositionX + 50, textPositionY, player.lives * 50, 20, RED);

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

	void updateBackground(Image& backgroundAnim, Texture& background, int& frames, float deltaTime)
	{
		animTimer += deltaTime;

		if (animTimer >= frameDelay)
		{
			// Move to next frame
			// NOTE: If final frame is reached we return to first frame
			currentAnimFrame++;
			
			if (currentAnimFrame >= frames) 
				currentAnimFrame = 0;

			// Get memory offset position for next frame data in image.data
			nextFrameDataOffset = backgroundAnim.width * backgroundAnim.height * 4 * currentAnimFrame;

			// Update GPU texture data with next frame image data
			// WARNING: Data size (frame size) and pixel format must match already created texture
			UpdateTexture(background, ((unsigned char*)backgroundAnim.data) + nextFrameDataOffset);

			animTimer -= frameDelay;
		}

	}
}