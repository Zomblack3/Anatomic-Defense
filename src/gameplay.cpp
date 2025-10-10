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
		playerFeatures::move(player, deltaTime);
		playerFeatures::rotate(player, deltaTime);

	}

	void draw(Player player)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		playerFeatures::drawPlayer(player);

		EndDrawing();
	}
}