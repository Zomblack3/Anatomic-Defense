#pragma once

#include <raylib.h>

namespace run
{
	void game();
}

namespace resources
{
	void loadResources(Font& font, Texture& MMBackground, Image& gameplayBackground, Texture& playerTexture);
	void unloadResources(Font& font, Texture& MMBackground, Image& gameplayBackground, Texture& playerTexture);
}