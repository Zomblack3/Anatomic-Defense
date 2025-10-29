#pragma once

#include "player.h"
#include "enemies.h"
#include "buttons.h"

namespace gameplay
{
	void gameplay(Player& player, std::vector <Enemy>& enemies, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Font font, Image& backgroundAnim, Texture& background, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy, int frames, Texture tutorialLeft, Texture tutorialRight);
}

namespace gameplayFeatures
{
	void update(Player& player, std::vector <Enemy>& enemies, float deltaTime, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Texture& gameplayBackground, Image& backgroundAnim, int frames, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy);
	void draw(Player player, std::vector <Enemy> enemies, Button buttons[], int amountOfButtons, Font font, Texture background, Texture tutorialLeft, Texture tutorialRight);
	void updateBackground(Image& backgroundAnim, Texture& background, int& frames, float deltaTime);
}