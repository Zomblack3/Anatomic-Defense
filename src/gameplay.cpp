#include "gameplay.h"

#include <iostream>

#include "settings.h"

bool isPauseOn = false;

namespace gameplay
{
	void gameplay(Player& player, std::vector <Enemy>& enemies, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Font font, Image& backgroundAnim, Texture& background, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy, int frames)
	{
		float deltaTime = GetFrameTime();

		gameplayFeatures::update(player, enemies, deltaTime, buttons, amountOfButtons, currentScreen, background, backgroundAnim, frames, smallEnemy, mediumEnemy, bigEnemy);

		gameplayFeatures::draw(player, enemies, buttons, amountOfButtons, font, background);
	}
}

namespace gameplayFeatures
{
	unsigned int nextFrameDataOffset = 0;  // Current byte offset to next frame in image.data

	int currentAnimFrame = 0;       // Current animation frame to load and draw
	float frameDelay = 1.0f / 30.0f;             // Frame delay to switch between animation frames
	float animTimer = 0.0f;           // General frames counter

	void update(Player& player, std::vector <Enemy>& enemies, float deltaTime, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Texture& gameplayBackground, Image& backgroundAnim, int frames, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy)
	{
		if (!isPauseOn)
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
				enemiesFeatures::checkBulletEnemyCollition(enemies, player, smallEnemy, mediumEnemy, bigEnemy);
				enemiesFeatures::checkPlayerEnemyCollition(enemies, player, deltaTime, smallEnemy, mediumEnemy, bigEnemy);
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

	void draw(Player player, std::vector <Enemy> enemies, Button buttons[], int amountOfButtons, Font font, Texture background)
	{
		int lifePositionX = 800;
		int textPositionY = 20;

		Vector2 scorePos = { 50.0f, static_cast <float> (textPositionY) };
		Vector2 scoreOrigin = { 0.0f, 0.0f };

		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(background, 0, 0, WHITE);

		playerShooting::drawBullets(player.bullets, maxAmountOfBullets);

		playerFeatures::drawPlayer(player);

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