#pragma once

#include "game.h"

#include "player.h"
#include "enemies.h"

namespace gameplay
{
	void gameplay(Player& player, std::vector <Enemy>& enemies);
}

namespace gameplayFeatures
{
	void update(Player& player, std::vector <Enemy>& enemies, float deltaTime);
	void draw(Player player, std::vector <Enemy> enemies);
}