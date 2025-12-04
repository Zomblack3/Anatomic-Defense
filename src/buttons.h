#pragma once

#include <iostream>
#include <raylib.h>

#include "screen.h"

struct Button
{
	Rectangle rec = { };

	int textSize = 20;

	float baseHeight = 50.0f;

	SCREEN directionScreen = SCREEN::MENU;

	std::string text = " ";

	Vector2 textPos = { };
	Vector2 backTexturePos = { };

	Texture frontTexture = { };
	Texture backTexture = { };

	Color unselectedButtonColor = WHITE;
	Color selectedButtonColor = RED;
	Color actualColor = unselectedButtonColor;
	Color unselectedTextColor = WHITE;
	Color selectedTextColor = YELLOW;
	Color actualTextColor = unselectedTextColor;
};

namespace buttonsFeatures
{
    bool collitionCheckButtonMouse(Rectangle rec);

    void setButtons(Button buttons[], int amountOfButtons, float startingPosX, float startingPosY, std::string texts[], SCREEN buttonScreen, Texture texture, Texture backTexture);
	void setSingleButton(Button& button, float x, float y, std::string text, SCREEN directionScreen, Texture frontTexture, Texture backTexture);

	void chageButtonState(Button& button);
    
	void drawButtons(Button buttons[], int amountOfButtons, Font font);
	void drawSingleButton(Button button, Font font);
}