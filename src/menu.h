#pragma once

#include <raylib.h>

#include "screen.h"
#include "buttons.h"

namespace mainFunctions
{
	void menu(SCREEN& currentScreen, Button buttons[], int amountOfButtons, Texture background, Font titleFont, Font normalFont);
}

namespace menuFunctions
{
	void update(SCREEN& currentScreen, Button buttons[], int amountOfButtons);
	void draw(Button buttons[], int amountOfButtons, Texture background, Font titleFont, Font normalFont);
}