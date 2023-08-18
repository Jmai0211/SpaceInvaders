#pragma once
#include "SDL_ttf.h"
#include "TextManager.h"
#include "Text.h"

class Game;

class MainMenu
{
public:
	// setup main menu related UI for display
	void SetUpMenu();

	void MenuConfirm();
	void MenuUp();
	void MenuDown();

	void OptionBack();
	void OptionLeft();
	void OptionRight();
	void OptionUp();
	void OptionDown();
private:
	// setup option menu related UI for display
	void SetUpOptions();

	// remove option menu related UI
	void UnsetOptions();

	// remove main menu related UI
	void UnsetMenu();

	// change the language of the game
	void ChangeLanguage();

	// convert resolution from integer values to characters that can be displayed as text
	const char* ConvertResolution(int width, int height);

	static Game* game;

	size_t menuIndex = 1;
	size_t optionIndex = 1;

	size_t languageIndex = 0;
	size_t resolutionIndex = 0;

	std::string resolutionString;
};

