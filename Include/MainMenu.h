#pragma once
#include "SDL_ttf.h"
#include "TextManager.h"
#include "Text.h"
#include "InputManager.h"

class Game;

class MainMenu
{
public:
	// setup main menu related UI for display
	void SetUpMenu();

	// handle input events when in menu
	void Input();

private:
	// setup option menu related UI for display
	void SetUpOptions();

	// remove option menu related UI
	void UnsetOptions();

	// remove main menu related UI
	void UnsetMenu();

	// highlight or unhighlight text
	void UpdateTextColor(Text* _text, bool highlight);

	// change the language of the game
	void ChangeLanguage();

	// convert resolution from integer values to characters that can be displayed as text
	const char* ConvertResolution(int width, int height);

	// handle main menu input
	void MenuNavigation();

	// handle option menu input
	void OptionNavigation();

	static Game* game;

	size_t menuIndex = 1;
	size_t optionIndex = 1;

	size_t languageIndex = 0;
	size_t resolutionIndex = 0;

	std::vector<Text*> menuText;
	std::vector<Text*> optionsText;

	std::string resolutionString;
};

