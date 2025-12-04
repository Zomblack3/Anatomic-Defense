#pragma once

#include <raylib.h>

namespace run
{
	void game();
}

namespace resources
{
	void loadResources(Texture& MMBackground, Texture& gameplayBackground, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShot, Texture& EGBackground, Sound& smallEnemyDeathSound, Sound& mediumEnemyDeathSound, Sound& bigEnemyDeathSound, Sound& playerHitSound, Font& baseFont, Font& titleFont, Texture& metalTexture, Texture& oldScreenTexture);
	void unloadResources(Font& font, Texture& MMBackground, Texture& gameplayBackground, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShot, Texture& EGBackground, Sound& smallEnemyDeathSound, Sound& mediumEnemyDeathSound, Sound& bigEnemyDeathSound, Font& titleFont, Texture& metalTexture, Texture& screenTexture, Sound& playerHitSound);
}