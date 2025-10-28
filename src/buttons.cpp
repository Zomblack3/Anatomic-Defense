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

	void setButtons(Button buttons[], int amountOfButtons, float startingPosX, float startingPosY, std::string texts[], SCREEN buttonScreen)
	{
		for (int i = 0; i < amountOfButtons; i++)
		{
			buttons[i].rec.width = texts[i].size() * buttons[i].textSize;
			buttons[i].rec.height = buttons[i].baseHeight;
			buttons[i].rec.y = startingPosY;
			buttons[i].rec.x = startingPosX - (buttons[i].rec.width / 2.0f);

			buttons[i].text = texts[i];

			buttons[i].textPos.x = buttons[i].rec.x + ((buttons[i].rec.width / 2.0f) - (MeasureText(texts[i].c_str(), buttons[i].textSize) / 2.0f));
			buttons[i].textPos.y = buttons[i].rec.y + buttons[i].textSize;

			switch (buttonScreen)
			{
			case SCREEN::MAIN_MENU:

				switch (i)
				{
				case 0:

					buttons[i].directionScreen = SCREEN::GAMEPLAY;

					break;
				case 1:

					buttons[i].directionScreen = SCREEN::OPTIONS;

					break;
				case 2:

					buttons[i].directionScreen = SCREEN::CREDITS;

					break;
				case 3:

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
			case SCREEN::END_SCREEN:

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
			case SCREEN::OPTIONS:

				switch (i)
				{
				case 3:

					buttons[i].directionScreen = SCREEN::MAIN_MENU;

					break;
				default:

					buttons[i].directionScreen = buttonScreen;

					break;
				}

				break;
			case SCREEN::EXIT:

				buttons[i].directionScreen = SCREEN::MAIN_MENU;

				/*switch (i)
				{
				default:

					buttons[i].directionScreen = SCREEN::MAIN_MENU;

					break;
				}*/

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

	void drawButtons(Button buttons[], int amountOfButtons)
	{
		for (int i = 0; i < amountOfButtons; i++)
		{
			if (!collitionCheckButtonMouse(buttons[i].rec))
			{
				DrawRectangle(static_cast <int>(buttons[i].rec.x), static_cast <int>(buttons[i].rec.y), static_cast <int>(buttons[i].rec.width), static_cast <int> (buttons[i].rec.height), buttons[i].actualColor);

				DrawText(buttons[i].text.c_str(), static_cast <int>(buttons[i].textPos.x), static_cast <int> (buttons[i].textPos.y), buttons[i].textSize, buttons[i].actualTextColor);
			}
			else
			{
				DrawRectangle(static_cast <int>(buttons[i].rec.x), static_cast <int>(buttons[i].rec.y), static_cast <int>(buttons[i].rec.width), static_cast <int>(buttons[i].rec.height), buttons[i].actualColor);

				DrawText(buttons[i].text.c_str(), static_cast <int>(buttons[i].textPos.x), static_cast <int> (buttons[i].textPos.y), buttons[i].textSize, buttons[i].actualTextColor);
			}
		}
	}
}
