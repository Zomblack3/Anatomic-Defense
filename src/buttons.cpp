#include "buttons.h"

namespace buttonsFeatures
{
	bool collitionCheckButtonMouse(Rectangle rec)
	{
		Vector2 mousePos = { };

		mousePos.x = static_cast <float> (GetMouseX());
		mousePos.y = static_cast <float> (GetMouseY());

		if (mousePos.x >= rec.x && mousePos.x <= rec.x + rec.width)
			if (mousePos.y >= rec.y && mousePos.y <= rec.y + rec.height)
				return true;

		return false;
	}

	void setButtons(Button buttons[], int amountOfButtons, float startingPosX, float startingPosY, std::string texts[], SCREEN buttonScreen, Texture frontTexture, Texture backTexture)
	{
		for (int i = 0; i < amountOfButtons; i++)
		{
			switch (buttonScreen)
			{
			case SCREEN::MENU:

				switch (i)
				{
				case 0:

					setSingleButton(buttons[i], startingPosX, startingPosY, texts[i], SCREEN::GAMEPLAY, frontTexture, backTexture);

					break;
				case 1:

					setSingleButton(buttons[i], startingPosX, startingPosY, texts[i], SCREEN::CREDITS, frontTexture, backTexture);

					break;
				case 2:

					setSingleButton(buttons[i], startingPosX, startingPosY, texts[i], SCREEN::EXIT, frontTexture, backTexture);

					break;
				default:



					break;
				}

				break;
			case SCREEN::GAMEPLAY:

				switch (i)
				{
				case 0:

					setSingleButton(buttons[i], startingPosX, startingPosY, texts[i], SCREEN::GAMEPLAY, frontTexture, backTexture);

					break;
				case 1:

					setSingleButton(buttons[i], startingPosX, startingPosY, texts[i], SCREEN::MENU, frontTexture, backTexture);

					break;
				default:



					break;
				}

				break;
			case SCREEN::END_GAME:

				switch (i)
				{
				case 0:

					setSingleButton(buttons[i], startingPosX, startingPosY, texts[i], SCREEN::GAMEPLAY, frontTexture, backTexture);

					break;
				case 1:

					setSingleButton(buttons[i], startingPosX, startingPosY, texts[i], SCREEN::MENU, frontTexture, backTexture);

					break;
				default:

					

					break;
				}

				break;
			case SCREEN::CREDITS:

				switch (i)
				{
				case 0:

					setSingleButton(buttons[i], startingPosX, startingPosY, texts[i], SCREEN::CREDITS_PROGRAMMERS, frontTexture, backTexture);

					break;
				case 1:

					setSingleButton(buttons[i], startingPosX, startingPosY, texts[i], SCREEN::CREDITS_ARTISTS, frontTexture, backTexture);

					break;
				case 2:

					setSingleButton(buttons[i], startingPosX, startingPosY, texts[i], SCREEN::CREDITS_MUSICIANS, frontTexture, backTexture);

					break;
				case 3:

					setSingleButton(buttons[i], startingPosX, startingPosY, texts[i], SCREEN::CREDITS_SOUND_ENGENNIERS, frontTexture, backTexture);

					break;
				case 4:

					setSingleButton(buttons[i], startingPosX, startingPosY, texts[i], SCREEN::CREDITS_FONTS, frontTexture, backTexture);

					break;
				default:



					break;
				}

				break;
			default:

				setSingleButton(buttons[i], startingPosX, startingPosY, texts[i], buttonScreen, frontTexture, backTexture);

				break;
			}

			startingPosY += buttons[i].rec.height * 2.0f;
		}
	}

	void setSingleButton(Button& button, float x, float y, std::string text, SCREEN directionScreen, Texture frontTexture, Texture backTexture)
	{
		float finalRecWidth = static_cast <float> (text.size() * button.textSize);

		int backTextureHeight = 0;
		int backTextureWidth = 0;
		float backTexturePosX = 0.0f;
		float backTexturePosY = 0.0f;

		Vector2 finalTextPos = { };

		float finalPosX = 0.0f;

		button.rec.width = finalRecWidth;
		button.rec.height = button.baseHeight;

		finalPosX = x - button.rec.width / 2.0f;

		button.rec.x = finalPosX;
		button.rec.y = y;

		button.text = text;

		button.frontTexture = frontTexture;
		button.backTexture = backTexture;

		button.directionScreen = directionScreen;

		backTextureHeight = static_cast <int> (button.rec.height + 10.0f);
		backTextureWidth = static_cast <int> (button.rec.width + 10.0f);

		backTexturePosX = button.rec.x - 5.0f;
		backTexturePosY = button.rec.y - 5.0f;

		button.frontTexture.width = static_cast <int> (button.rec.width);
		button.frontTexture.height = static_cast <int> (button.rec.height);

		button.backTexture.width = backTextureWidth;
		button.backTexture.height = backTextureHeight;

		button.backTexturePos.x = backTexturePosX;
		button.backTexturePos.y = backTexturePosY;

		finalTextPos.x = button.rec.x + (button.rec.width / 4.0f);
		finalTextPos.y = button.rec.y + (button.rec.height / 4.0f);

		button.textPos = finalTextPos;
	}

	void chageButtonState(Button& button)
	{
		if (collitionCheckButtonMouse(button.rec))
		{
			button.actualColor = button.selectedButtonColor;

			button.actualTextColor = button.selectedTextColor;
		}
		else
		{
			button.actualColor = button.unselectedButtonColor;

			button.actualTextColor = button.unselectedTextColor;
		}
	}

	void drawButtons(Button buttons[], int amountOfButtons, Font font)
	{
		for (int i = 0; i < amountOfButtons; i++)
			drawSingleButton(buttons[i], font);
	}

	void drawSingleButton(Button button, Font font)
	{
		DrawRectangleRec(button.rec, button.actualColor);

		DrawTexture(button.backTexture, static_cast <int>(button.backTexturePos.x), static_cast <int>(button.backTexturePos.y), WHITE);
		DrawTexture(button.frontTexture, static_cast <int>(button.rec.x), static_cast <int>(button.rec.y), button.actualColor);

		DrawTextEx(font, button.text.c_str(), button.textPos, static_cast <float>(button.textSize), 2, button.actualTextColor);
	}
}
