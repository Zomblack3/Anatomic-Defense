#include "menu.h"

#include "settings.h"

namespace mainFunctions
{
	void menu(SCREEN& currentScreen, Button buttons[], int amountOfButtons, Texture background, Font titleFont, Font normalFont)
	{
		menuFunctions::update(currentScreen, buttons, amountOfButtons);

		menuFunctions::draw(buttons, amountOfButtons, background, titleFont, normalFont);
	}
}

namespace menuFunctions
{
	void update(SCREEN& currentScreen, Button buttons[], int amountOfButtons)
	{
		for (int i = 0; i < amountOfButtons; i++)
		{
			buttonsFeatures::chageButtonState(buttons[i]);

			if (buttonsFeatures::collitionCheckButtonMouse(buttons[i].rec))
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					if (buttons[i].directionScreen != currentScreen)
						currentScreen = buttons[i].directionScreen;
				}
			}
		}
	}

	void draw(Button buttons[], int amountOfButtons, Texture background, Font titleFont, Font normalFont)
	{
		std::string titleText = "ANATOMIC DEFENSE";

		Vector2 titleLenght = MeasureTextEx(titleFont, titleText.c_str(), titleTextSize, textSpacing);

		Rectangle titleRec = { };
		Vector2 titlePos = { };

		float finalTitleRecWidth = titleLenght.x + 40.0f;
		float finalTitleRecHeight = titleLenght.y + 20.0f;

		titleRec.width = finalTitleRecWidth;
		titleRec.height = finalTitleRecHeight;
		titleRec.x = screenWidth / 2.0f - titleRec.width / 2.0f;
		titleRec.y = screenHeight / 7.0f;

		titlePos.x = screenWidth / 2.0f - titleLenght.x / 2.0f;
		titlePos.y = titleRec.y + (titleRec.height / 6.0f);

		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(background, 0, 0, WHITE);

		DrawRectangle(static_cast <int> (titleRec.x), static_cast <int> (titleRec.y), static_cast <int> (titleRec.width), static_cast <int> (titleRec.height), RED);
		DrawTextEx(titleFont, titleText.c_str(), titlePos, titleTextSize, textSpacing, WHITE);

		buttonsFeatures::drawButtons(buttons, amountOfButtons, normalFont);

		DrawText("Creado por Zomblack3 (Santiago Britos)", 10, static_cast <int> (screenHeight) - 30, 30, BLACK);

		EndDrawing();
	}
}