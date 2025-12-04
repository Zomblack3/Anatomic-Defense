#pragma once

#include <raylib.h>

namespace run
{
	void game();
}

namespace resources
{
	void loadResources(Texture& MMBackground, Texture& gameplayBackground, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShot, Texture& EGBackground, Sound& smallEnemyDeathSound, Sound& mediumEnemyDeathSound, Sound& bigEnemyDeathSound);
	void unloadResources(Font& font, Texture& MMBackground, Texture& gameplayBackground, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShot, Texture& EGBackground, Sound& smallEnemyDeathSound, Sound& mediumEnemyDeathSound, Sound& bigEnemyDeathSound);
}