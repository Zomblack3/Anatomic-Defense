#include "buttons.h"

#include "settings.h"

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

	void setButtons(Button buttons[], int amountOfButtons, float startingPosX, float startingPosY, std::string texts[], SCREEN buttonScreen, Texture texture, Texture backTexture)
	{
		for (int i = 0; i < amountOfButtons; i++)
		{
			buttons[i].rec.width = static_cast <float> (texts[i].size() * buttons[i].textSize);
			buttons[i].rec.height = buttons[i].baseHeight;
			buttons[i].rec.y = startingPosY;
			buttons[i].rec.x = startingPosX - (buttons[i].rec.width / 2.0f);

			buttons[i].text = texts[i];

			buttons[i].textPos.x = buttons[i].rec.x + (buttons[i].rec.width / 4.0f);
			buttons[i].textPos.y = buttons[i].rec.y + (buttons[i].rec.height / 4.0f);

			buttons[i].frontTexture = texture;
			buttons[i].backTexture = backTexture;

			buttons[i].frontTexture.height = static_cast <int> (buttons[i].rec.height);
			buttons[i].frontTexture.width = static_cast <int> (buttons[i].rec.width);

			buttons[i].backTexture.height = static_cast <int> (buttons[i].rec.height + 10.0f);
			buttons[i].backTexture.width = static_cast <int> (buttons[i].rec.width + 10.0f);

			buttons[i].backTexturePos.x = buttons[i].rec.x - 5.0f;
			buttons[i].backTexturePos.y = buttons[i].rec.y - 5.0f;

			switch (buttonScreen)
			{
			case SCREEN::MAIN_MENU:

				switch (i)
				{
				case 0:

					buttons[i].directionScreen = SCREEN::GAMEPLAY;

					break;
				case 1:
					
					buttons[i].directionScreen = SCREEN::CREDITS;

					break;
				case 2:

					buttons[i].directionScreen = SCREEN::EXIT;

					break;
				default:

					buttons[i].directionScreen = buttonScreen;

					break;
				}

				break;
			case SCREEN::GAMEPLAY:

				switch (i)
				{
				case 1:

					buttons[i].directionScreen = SCREEN::MAIN_MENU;

					break;
				default:
					break;
				}

				break;
			case SCREEN::END_GAME:

				switch (i)
				{
				case 0:

					buttons[i].directionScreen = SCREEN::GAMEPLAY;

					break;
				case 1:

					buttons[i].directionScreen = SCREEN::MAIN_MENU;

					break;
				default:

					buttons[i].directionScreen = buttonScreen;

					break;
				}

				break;
			case SCREEN::EXIT:

				buttons[i].directionScreen = SCREEN::MAIN_MENU;

				break;
			default:
				break;
			}

			startingPosY += buttons[i].rec.height * 2.0f;
		}
	}

	void chageButtonState(Button & button)
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
		{
			if (!collitionCheckButtonMouse(buttons[i].rec))
			{
				DrawRectangle(static_cast <int> (buttons[i].rec.x), static_cast <int> (buttons[i].rec.y), static_cast <int>(buttons[i].rec.width), static_cast <int> (buttons[i].rec.height), buttons[i].actualColor);

				DrawTexture(buttons[i].backTexture, static_cast <int>(buttons[i].backTexturePos.x), static_cast <int>(buttons[i].backTexturePos.y), WHITE);
				DrawTexture(buttons[i].frontTexture, static_cast <int>(buttons[i].rec.x), static_cast <int>(buttons[i].rec.y), buttons[i].actualColor);

				DrawTextEx(font, buttons[i].text.c_str(), buttons[i].textPos, static_cast <float>(buttons[i].textSize), 2, buttons[i].actualTextColor);
			}
			else
			{
				DrawRectangle(static_cast <int> (buttons[i].rec.x), static_cast <int>(buttons[i].rec.y), static_cast <int>(buttons[i].rec.width), static_cast <int>(buttons[i].rec.height), buttons[i].actualColor);

				DrawTexture(buttons[i].backTexture, static_cast <int>(buttons[i].backTexturePos.x), static_cast <int>(buttons[i].backTexturePos.y), WHITE);
				DrawTexture(buttons[i].frontTexture, static_cast <int>(buttons[i].rec.x), static_cast <int>(buttons[i].rec.y), buttons[i].actualColor);
				
				DrawTextEx(font, buttons[i].text.c_str(), buttons[i].textPos, static_cast <float>(buttons[i].textSize), 2, buttons[i].actualTextColor);
			}
		}
	}
}
