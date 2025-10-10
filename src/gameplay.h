#pragma once

#include "game.h"

#include "player.h"

namespace gameplay
{
	void gameplay(Player& player);
}

namespace gameplayFeatures
{
	void update(Player& player, float deltaTime);
	void draw(Player player);
}