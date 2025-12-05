#include "endGame.h"

namespace mainFunctions
{
	void endGame(Player& player, std::vector <Enemy>& enemies, Button buttons[], int amountOfButtons, SCREEN& currentScreen, Font font1, Font font2, Texture background)
	{
		endGameFunctions::update(player, enemies, buttons, amountOfButtons, currentScreen);

		endGameFunctions::draw(player, buttons, amountOfButtons, font1, font2, background);
	}
}

namespace endGameFunctions
{
	void update(Player& player, std::vector <Enemy>& enemies, Button buttons[], int amountOfButtons, SCREEN& currentScreen)
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

					if (currentScreen != SCREEN::END_GAME)
					{
						playerFeatures::setDefault(player);
						enemies.clear();
					}
				}
			}
		}
	}

	void draw(Player player, Button buttons[], int amountOfButtons, Font font1, Font font2, Texture background)
	{
		/* Texts */
		std::string titleText = "FIN DEL JUEGO";

		std::string lifesText = TextFormat("Vidas: %i", player.lifes);
		std::string scoreText = TextFormat("Puntaje: %i", player.score);

		/* Texts length */
		Vector2 titleTextLength = MeasureTextEx(font1, titleText.c_str(), titleTextSize, textSpacing);

		Vector2 lifesTextLength = MeasureTextEx(font1, lifesText.c_str(), titleTextSize, textSpacing);
		Vector2 scoreTextLength = MeasureTextEx(font1, scoreText.c_str(), titleTextSize, textSpacing);

		/* Texts positions */
		Vector2 titleTextPos = { (screenWidth / 2.0f) - (titleTextLength.x / 2.0f), (screenHeight / 2.0f) - (screenHeight / 6.0f) };

		Vector2 lifesTextPos = { (screenWidth / 2.0f) - (lifesTextLength.x / 2.0f), (screenHeight / 2.0f) - 50.0f };
		Vector2 scoreTextPos = { (screenWidth / 2.0f) - (scoreTextLength.x / 2.0f), screenHeight / 2.0f };

		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(background, 0, 0, WHITE);

		DrawTextEx(font1, titleText.c_str(), titleTextPos, titleTextSize, textSpacing, BLACK);

		buttonsFeatures::drawButtons(buttons, amountOfButtons, font2);

		DrawTextEx(font1, scoreText.c_str(), scoreTextPos, titleTextSize, textSpacing, BLACK);
		DrawTextEx(font1, lifesText.c_str(), lifesTextPos, titleTextSize, textSpacing, BLACK);

		EndDrawing();
	}
}