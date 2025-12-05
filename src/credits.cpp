#include "credits.h"

#include "settings.h"

const int amountOfProgrammingButtons = 1;
const int amountOfArtButtons = 5;
const int amountOfMusicButtons = 2;
const int amountOfSoundsButtons = 4;
const int amountOfFontButtons = 2;

namespace mainFunctions
{
	void credits(SCREEN& currentScreen, Button& returnMenuButton, Button& returnCreditsButton, Button buttons[], int amountOfButtons, Texture background, Texture frontTexture, Texture backTexture, Font baseFont)
	{
		Vector2 buttonsStartingPos = { screenWidth / 2.0f, (screenHeight / 2.0f) - 250.0f };

		// Credits buttons //

		/* Buttons texts*/
		std::string programmingTexts[amountOfProgrammingButtons] = { "Zomblack3" };
		std::string artTexts[amountOfArtButtons] = { "CreativeSpace [Enemigos]", "freepik [Fondo de fin del juego, Textura frontal de botones]", "template.net [Textura contorno de botones]", "Quimono [Fondo del juego]", "Zomblack3 [Jugador]" };
		std::string musicTexts[amountOfMusicButtons] = { "denwriteman [Musica del juego]", "Megisss [Musica del menu]" };
		std::string soundsTexts[amountOfSoundsButtons] = { "bolkmar [Disparo de jugador]", "Zuzek06 [Muerte del enemigo pequeno]", "qudobup [Muerte del enemigo mediano y grande]", "Jofae [Choque de la nave]" };
		std::string fontsTexts[amountOfFontButtons] = { "Dusit Supasawat [Ds-Digital]", "Google [Roboto]" };

		/* Buttons */
		Button programmingButtons[amountOfProgrammingButtons] = { };
		Button artButtons[amountOfArtButtons] = { };
		Button musicButtons[amountOfMusicButtons] = { };
		Button soundsButtons[amountOfSoundsButtons] = { };
		Button fontsButtons[amountOfFontButtons] = { };

		/* Set Buttons */
		buttonsFeatures::setButtons(programmingButtons, amountOfProgrammingButtons, buttonsStartingPos.x, buttonsStartingPos.y, programmingTexts, SCREEN::CREDITS_PROGRAMMERS, frontTexture, backTexture, baseFont);
		buttonsFeatures::setButtons(artButtons, amountOfArtButtons, buttonsStartingPos.x, buttonsStartingPos.y, artTexts, SCREEN::CREDITS_ARTISTS, frontTexture, backTexture, baseFont);
		buttonsFeatures::setButtons(musicButtons, amountOfMusicButtons, buttonsStartingPos.x, buttonsStartingPos.y, musicTexts, SCREEN::CREDITS_MUSICIANS, frontTexture, backTexture, baseFont);
		buttonsFeatures::setButtons(soundsButtons, amountOfSoundsButtons, buttonsStartingPos.x, buttonsStartingPos.y, soundsTexts, SCREEN::CREDITS_SOUND_ENGENNIERS, frontTexture, backTexture, baseFont);
		buttonsFeatures::setButtons(fontsButtons, amountOfFontButtons, buttonsStartingPos.x, buttonsStartingPos.y, fontsTexts, SCREEN::CREDITS_FONTS, frontTexture, backTexture, baseFont);

		creditsFunctions::update(currentScreen, buttons, returnMenuButton, returnCreditsButton, amountOfButtons, programmingButtons, artButtons, musicButtons, soundsButtons, fontsButtons);

		creditsFunctions::draw(currentScreen, buttons, returnMenuButton, returnCreditsButton, amountOfButtons, background, baseFont, programmingButtons, artButtons, musicButtons, soundsButtons, fontsButtons);
	}
}

namespace creditsFunctions
{
	void update(SCREEN& currentScreen, Button buttons[], Button& returnMenuButton, Button& returnCreditsButton, int amountOfButtons, Button programmersButtons[], Button artButtons[], Button musicButtons[], Button soundsButtons[], Button fontButtons[])
	{		
		switch (currentScreen)
		{
		case SCREEN::CREDITS:

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

			buttonsFeatures::chageButtonState(returnMenuButton);

			if (buttonsFeatures::collitionCheckButtonMouse(returnMenuButton.rec))
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					if (returnMenuButton.directionScreen != currentScreen)
						currentScreen = returnMenuButton.directionScreen;
				}
			}

			break;
		case SCREEN::CREDITS_PROGRAMMERS:
			
			for (int i = 0; i < amountOfProgrammingButtons; i++)
			{
				buttonsFeatures::chageButtonState(programmersButtons[i]);

				if (buttonsFeatures::collitionCheckButtonMouse(programmersButtons[i].rec))
				{
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
						OpenURL("https://github.com/Zomblack3");
				}
			}

			buttonsFeatures::chageButtonState(returnCreditsButton);

			if (buttonsFeatures::collitionCheckButtonMouse(returnCreditsButton.rec))
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					if (returnCreditsButton.directionScreen != currentScreen)
						currentScreen = returnCreditsButton.directionScreen;
				}
			}
			
			break;
		case SCREEN::CREDITS_ARTISTS:
			
			for (int i = 0; i < amountOfArtButtons; i++)
			{
				buttonsFeatures::chageButtonState(artButtons[i]);

				if (buttonsFeatures::collitionCheckButtonMouse(artButtons[i].rec))
				{
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						switch (i)
						{
						case 0:
							
							OpenURL("https://www.freepik.es/vector-gratis/conjunto-virus-realistas-3d_21297314.htm#fromView=author&page=1&position=7&uuid=0e056b07-a647-42db-add6-577ce35bb2ac");

							break;
						case 1:

							OpenURL("https://www.freepik.com/free-vector/gradient-grid-background_49248097.htm#fromView=search&page=1&position=46&uuid=c5cdc580-1bb7-42c2-b728-f9163c5023d9&query=Computer+terminal+texture");
							OpenURL("https://www.freepik.es/foto-gratis/vista-lapida-flores-velas_27506591.htm#fromView=search&page=1&position=4&uuid=271b0aed-24e1-4492-86e2-546a42b16015&query=Lapida");

							break;
						case 2:

							OpenURL("https://www.template.net/design-templates/textures/brushed-metal-texture/");

							break;
						case 3:

							OpenURL("https://pixabay.com/es/illustrations/c%c3%a9lulas-rojo-m%c3%a9dico-medicamento-1813410/");

							break;
						case 4:

							OpenURL("https://github.com/Zomblack3");

							break;
						default:
							break;
						}
					}
				}
			}

			buttonsFeatures::chageButtonState(returnCreditsButton);

			if (buttonsFeatures::collitionCheckButtonMouse(returnCreditsButton.rec))
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					if (returnCreditsButton.directionScreen != currentScreen)
						currentScreen = returnCreditsButton.directionScreen;
				}
			}
			
			break;
		case SCREEN::CREDITS_MUSICIANS:
			
			for (int i = 0; i < amountOfMusicButtons; i++)
			{
				buttonsFeatures::chageButtonState(musicButtons[i]);

				if (buttonsFeatures::collitionCheckButtonMouse(musicButtons[i].rec))
				{
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						switch (i)
						{
						case 0:

							OpenURL("https://pixabay.com/music/techno-trance-den-writeman-project-5-411115/");

							break;
						case 1:

							OpenURL("https://pixabay.com/music/beats-modern-medical-background-426195/");

							break;
						default:
							break;
						}
					}
				}
			}

			buttonsFeatures::chageButtonState(returnCreditsButton);

			if (buttonsFeatures::collitionCheckButtonMouse(returnCreditsButton.rec))
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					if (returnCreditsButton.directionScreen != currentScreen)
						currentScreen = returnCreditsButton.directionScreen;
				}
			}
			
			break;
		case SCREEN::CREDITS_SOUND_ENGENNIERS:
			
			for (int i = 0; i < amountOfSoundsButtons; i++)
			{
				buttonsFeatures::chageButtonState(soundsButtons[i]);

				if (buttonsFeatures::collitionCheckButtonMouse(soundsButtons[i].rec))
				{
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						switch (i)
						{
						case 0:

							OpenURL("https://freesound.org/people/bolkmar/sounds/421704/");

							break;
						case 1:

							OpenURL("https://freesound.org/people/Zuzek06/sounds/353250/");

							break;
						case 2:

							OpenURL("https://freesound.org/people/qubodup/sounds/751342/");
							OpenURL("https://freesound.org/people/qubodup/sounds/751340/");

							break;
						case 3:

							OpenURL("https://freesound.org/people/Jofae/sounds/361636/");

							break;
						default:
							break;
						}
					}
				}
			}

			buttonsFeatures::chageButtonState(returnCreditsButton);

			if (buttonsFeatures::collitionCheckButtonMouse(returnCreditsButton.rec))
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					if (returnCreditsButton.directionScreen != currentScreen)
						currentScreen = returnCreditsButton.directionScreen;
				}
			}
			
			break;
		case SCREEN::CREDITS_FONTS:

			for (int i = 0; i < amountOfFontButtons; i++)
			{
				buttonsFeatures::chageButtonState(fontButtons[i]);

				if (buttonsFeatures::collitionCheckButtonMouse(fontButtons[i].rec))
				{
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						switch (i)
						{
						case 0:

							OpenURL("https://www.dafont.com/ds-digital.font");

							break;
						case 1:

							OpenURL("https://www.dafont.com/roboto.font");

							break;
						default:
							break;
						}
					}
				}
			}

			buttonsFeatures::chageButtonState(returnCreditsButton);

			if (buttonsFeatures::collitionCheckButtonMouse(returnCreditsButton.rec))
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					if (returnCreditsButton.directionScreen != currentScreen)
						currentScreen = returnCreditsButton.directionScreen;
				}
			}

			break;
		default:



			break;
		}

	}

	void draw(SCREEN currentScreen, Button buttons[], Button returnMenuButton, Button returnCreditsButton, int amountOfButtons, Texture background, Font baseFont, Button programmersButtons[], Button artButtons[], Button musicButtons[], Button soundsButtons[], Button fontButtons[])
	{
		background.width = screenWidth;
		background.height = screenHeight;

		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(background, 0, 0, WHITE);

		switch (currentScreen)
		{
		case SCREEN::CREDITS:
			
			buttonsFeatures::drawButtons(buttons, amountOfButtons, baseFont);

			buttonsFeatures::drawSingleButton(returnMenuButton, baseFont);
			
			break;
		case SCREEN::CREDITS_PROGRAMMERS:
			
			buttonsFeatures::drawButtons(programmersButtons, amountOfProgrammingButtons, baseFont);

			buttonsFeatures::drawSingleButton(returnCreditsButton, baseFont);
			
			break;
		case SCREEN::CREDITS_ARTISTS:
			
			buttonsFeatures::drawButtons(artButtons, amountOfArtButtons, baseFont);

			buttonsFeatures::drawSingleButton(returnCreditsButton, baseFont);
			
			break;
		case SCREEN::CREDITS_MUSICIANS:
			
			buttonsFeatures::drawButtons(musicButtons, amountOfMusicButtons, baseFont);

			buttonsFeatures::drawSingleButton(returnCreditsButton, baseFont);
			
			break;
		case SCREEN::CREDITS_SOUND_ENGENNIERS:
			
			buttonsFeatures::drawButtons(soundsButtons, amountOfSoundsButtons, baseFont);

			buttonsFeatures::drawSingleButton(returnCreditsButton, baseFont);
			
			break;
		case SCREEN::CREDITS_FONTS:

			buttonsFeatures::drawButtons(fontButtons, amountOfFontButtons, baseFont);

			buttonsFeatures::drawSingleButton(returnCreditsButton, baseFont);

			break;
		default:
			break;
		}

		EndDrawing();
	}
}