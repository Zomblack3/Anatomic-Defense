#pragma once

#include <raylib.h>

namespace run
{
	void game();
}

namespace resources
{
	void loadResources(Texture& MMBackground, Texture& gameplayBackground, Image& backgroundAnim, Texture& playerTexture, int& frames, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShot);
	void unloadResources(Font& font, Texture& MMBackground, Texture& gameplayBackground, Image& backgroundAnim, Texture& playerTexture, Texture& smallEnemy, Texture& mediumEnemy, Texture& bigEnemy, Texture& tutorialLeft, Texture& tutorialRight, Sound& playerShot);
}