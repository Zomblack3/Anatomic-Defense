#pragma once

#include <iostream>
#include <raylib.h>

#include "screen.h"

struct Button
{
	Rectangle rec = { };

	int textSize = 20;

	float baseHeight = 50.0f;

	SCREEN directionScreen = SCREEN::MAIN_MENU;

	std::string text = " ";

	Vector2 textPos = { };

	Color unselectedButtonColor = WHITE;
	Color selectedButtonColor = DARKBLUE;
	Color actualColor = unselectedButtonColor;
	Color unselectedTextColor = BLACK;
	Color selectedTextColor = YELLOW;
	Color actualTextColor = unselectedTextColor;
};

namespace buttonsFeatures
{
    bool collitionCheckButtonMouse(Rectangle rec);

    void setButtons(Button buttons[], int amountOfButtons, float startingPosX, float startingPosY, std::string texts[], SCREEN buttonScreen, Font font);
    void chageButtonState(Button& button);
    void drawButtons(Button buttons[], int amountOfButtons, Font font);
}