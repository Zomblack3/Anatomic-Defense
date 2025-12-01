#pragma once

#include "player.h"
#include "enemies.h"
#include "buttons.h"

namespace mainFunctions
{
	void endGame(Player& player, std::vector <Enemy>& enemies, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Font font1, Font font2, Texture background);
}

namespace endGameFunctions
{
	void update(Player& player, std::vector <Enemy>& enemies, Button buttons[], int amountOfButtons, SCREEN& currentScreen);
	void draw(Player player, Button buttons[], int amountOfButtons, Font font1, Font font2, Texture background);
}