#pragma once
#include "SDL_ttf.h"
#include "TextManager.h"
#include "Text.h"
#include "InputManager.h"

class Game;

class MainMenu
{
public:

	void SetUpMenu();

	void Input();

private:
	void SetUpOptions();
	void UnsetOptions();

	void UnsetMenu();

	void UpdateTextColor(Text* _text, bool highlight);
	void ChangeLanguage();
	const char* ConvertResolution(int width, int height);

	void MenuNavigation();
	void OptionNavigation();

	static Game* game;

	size_t menuIndex = 1;

	bool options = false;

	size_t optionIndex = 1;
	size_t languageIndex = 0;
	size_t resolutionIndex = 0;

	std::vector<Text*> menuText;
	std::vector<Text*> optionsText;

	std::string resolutionString;
};

