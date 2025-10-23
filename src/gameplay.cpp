#include "gameplay.h"

#include <iostream>

using namespace gameplayFeatures;

namespace gameplay
{
	void gameplay(Player& player, std::vector <Enemy>& enemies)
	{
		float deltaTime = GetFrameTime() * 100;

		update(player, enemies, deltaTime);

		draw(player, enemies);
	}
}

namespace gameplayFeatures
{
	void update(Player& player, std::vector <Enemy>& enemies, float deltaTime)
	{
		enemiesFeatures::spawnEnemy(enemies, deltaTime);

		playerFeatures::setPlayerDirection(player);
		playerFeatures::movePlayer(player, deltaTime);
		playerFeatures::rotatePlayer(player);

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
			playerShooting::shootBullet(player, player.bullets, maxAmountOfBullets);

		playerShooting::moveBullet(player.bullets, maxAmountOfBullets, deltaTime);

		if (enemies.size() > 0)
		{
			enemiesFeatures::moveEnemy(enemies, deltaTime);
			enemiesFeatures::checkBulletEnemyCollition(enemies, player);
			enemiesFeatures::checkPlayerEnemyCollition(enemies, player, deltaTime);
		}
	}

	void draw(Player player, std::vector <Enemy> enemies)
	{
		int lifePosition = 800;
		int textPositionY = 20;

		BeginDrawing();

		ClearBackground(BLACK);

		playerFeatures::drawPlayer(player);

		playerShooting::drawBullets(player.bullets, maxAmountOfBullets);

		enemiesFeatures::drawEnemy(enemies);

		DrawRectangle(0, 0, settings::screenWidth, 50, WHITE);

		DrawText(TextFormat("Score: %i", player.score), 50, textPositionY, 20, BLACK);
		DrawText("Vida: ", lifePosition, textPositionY, 20, BLACK);
		DrawRectangle(lifePosition + 50, textPositionY, player.health, 20, RED);

		DrawLine(static_cast <int> (player.v1.x), static_cast <int> (player.v1.y), GetMouseX(), GetMouseY(), YELLOW);

		EndDrawing();
	}
}