#pragma once

#include "player.h"
#include "enemies.h"
#include "buttons.h"

namespace mainFunctions
{
	void gameplay(Player& player, std::vector <Enemy>& enemies, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Font font, Texture& background, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy, Texture tutorialLeft, Texture tutorialRight, Texture hudTexture, Texture hudValuesTexture);
}

namespace gameplayFunctions
{
	void update(Player& player, std::vector <Enemy>& enemies, float deltaTime, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy);
	void draw(Player player, std::vector <Enemy> enemies, Button buttons[], int amountOfButtons, Font font, Texture background, Texture tutorialLeft, Texture tutorialRight, Texture hudTexture, Texture hudValuesTexture);
}