#include "gameplay.h"

using namespace gameplayFeatures;

namespace gameplay
{
	void gameplay(Player& player)
	{
		float deltaTime = GetFrameTime() * 100;

		update(player, deltaTime);

		draw(player);
	}
}

namespace gameplayFeatures
{
	void update(Player& player, float deltaTime)
	{
		playerFeatures::setPlayerDirection(player);
		playerFeatures::movePlayer(player, deltaTime);
		playerFeatures::rotatePlayer(player);

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
			playerShooting::shootBullet(player, player.bullets, maxAmountOfBullets);

		playerShooting::moveBullet(player.bullets, maxAmountOfBullets, deltaTime);
	}

	void draw(Player player)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		playerFeatures::drawPlayer(player);

		playerShooting::drawBullets(player.bullets, maxAmountOfBullets);

		DrawLine(static_cast <int> (player.v1.x), static_cast <int> (player.v1.y), GetMouseX(), GetMouseY(), YELLOW);

		EndDrawing();
	}
}