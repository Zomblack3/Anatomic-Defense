#pragma once

#include "player.h"
#include "enemies.h"
#include "buttons.h"

namespace gameplay
{
	void gameplay(Player& player, std::vector <Enemy>& enemies, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Font font, Image background);
}

namespace gameplayFeatures
{
	void update(Player& player, std::vector <Enemy>& enemies, float deltaTime, Button buttons[], int amountOfButtons, SCREEN& currentScreen);
	void draw(Player player, std::vector <Enemy> enemies, Button buttons[], int amountOfButtons, Font font, Image background);
}