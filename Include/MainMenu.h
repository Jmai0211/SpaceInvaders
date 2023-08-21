#pragma once
#include "SDL_ttf.h"
#include "TextManager.h"
#include "Text.h"

class Game;

class MainMenu
{
public:
	// Setup main menu related UI for display
	void SetUpMenu();

	// Select main menu item
	void MenuConfirm();
	// Main menu go up
	void MenuUp();
	// Main menu go down
	void MenuDown();

	// Options menu go back to main menu
	void OptionBack();
	// Options menu go left
	void OptionLeft();
	// Options menu go right
	void OptionRight();
	// Options menu go up
	void OptionUp();
	// Options menu go down
	void OptionDown();
private:
	// Setup option menu related UI for display
	void SetUpOptions();

	// Remove option menu related UI
	void UnsetOptions();

	// Remove main menu related UI
	void UnsetMenu();

	// Change the language of the game
	void ChangeLanguage();

	// Convert resolution from integer values to characters that can be displayed as text
	const char* ConvertResolution(int width, int height);

	static Game* game;

	size_t menuIndex = 1;
	size_t optionIndex = 1;

	size_t languageIndex = 0;
	size_t resolutionIndex = 0;

	std::string resolutionString;
};

