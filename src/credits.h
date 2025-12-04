#pragma once

#include "buttons.h"

namespace mainFunctions
{
	void credits(SCREEN& currentScreen, Button& returnMenuButton, Button& returnCreditsButton, Button buttons[], int amountOfButtons, Texture background, Texture frontTexture, Texture backTexture, Font baseFont);
}

namespace creditsFunctions
{
	void update(SCREEN& currentScreen, Button buttons[], Button& returnMenuButton, Button& returnCreditsButton, int amountOfButtons, Button programmersButtons[], Button artButtons[], Button musicButtons[], Button soundsButtons[], Button fontButtons[]);
	void draw(SCREEN currentScreen, Button buttons[], Button returnMenuButton, Button returnCreditsButton, int amountOfButtons, Texture background, Font baseFont, Button programmersButtons[], Button artButtons[], Button musicButtons[], Button soundsButtons[], Button fontButtons[]);
}