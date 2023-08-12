#include "MainMenu.h"
#include "GameManager.h"
#include "Game.h"
#include <string>
#include "CommonStructs.h"
#include "TextureManager.h"
#include "AssetManager.h"

Game* MainMenu::game;
Uint32 lastMenuChangeTime = 0;

const char* languageText;

// setup main menu
void MainMenu::SetUpMenu()
{
	GameManager::GetInstance().SetState(GameManager::GameState::Menu);
	menuIndex = 1;
	menuText.push_back(TextManager::AddText(960, 230, TextManager::GetLocalizedText("Space Invaders")));
	menuText[0]->SetScale(2, 2);

	menuText.push_back(TextManager::AddText(960, 500, TextManager::GetLocalizedText("Start Game")));
	menuText.push_back(TextManager::AddText(960, 700, TextManager::GetLocalizedText("Options")));
	menuText.push_back(TextManager::AddText(960, 900, TextManager::GetLocalizedText("Exit Game")));

	UpdateTextColor(menuText[menuIndex], true);
}

// setup options menu
void MainMenu::SetUpOptions()
{
	GameManager::GetInstance().SetState(GameManager::GameState::Option);
	UnsetMenu();

	languageIndex = static_cast<int>(GameManager::GetInstance().GetLanguage());

	optionIndex = 2;

	for (size_t i = 0; i < sizeof(resolutionTable) / sizeof(resolutionTable[0]); i++)
	{
		if (resolutionTable[i].width == GameManager::GetInstance().GetResolution().first &&
			resolutionTable[i].height == GameManager::GetInstance().GetResolution().second)
		{
			resolutionIndex = static_cast<int>(i);
			break;
		}
	}

	optionsText.push_back(TextManager::AddText(960, 230, TextManager::GetLocalizedText("Options")));
	optionsText[0]->SetScale(2, 2);

	optionsText.push_back(TextManager::AddText(650, 500, TextManager::GetLocalizedText("Language")));

	optionsText.push_back(TextManager::AddText(1250, 500, TextManager::GetLocalizedText("English")));

	optionsText.push_back(TextManager::AddText(650, 700, TextManager::GetLocalizedText("Resolution")));

	optionsText.push_back(TextManager::AddText(1250, 700, ConvertResolution(GameManager::GetInstance().GetResolution().first, GameManager::GetInstance().GetResolution().second)));

	UpdateTextColor(optionsText[optionIndex], true);
}

// clear options list to avoid memory leak / unnecessary memory usage
void MainMenu::UnsetOptions()
{
	for (size_t i = 0; i < optionsText.size(); i++)
	{
		delete optionsText[i];
	}
	optionsText.clear();
}

// clear menu list to avoid memory leak / unnecessary memory usage
void MainMenu::UnsetMenu()
{
	for (size_t i = 0; i < menuText.size(); i++)
	{
		delete menuText[i];
	}
	menuText.clear();
}

// handle menu input
void MainMenu::Input()
{
	// stop continuous input
	if (SDL_GetTicks() - lastMenuChangeTime >= 100)
	{
		switch (GameManager::GetInstance().GetState())
		{
		case GameManager::GameState::Menu:
			// main menu input
			MenuNavigation();
			break;
		case GameManager::GameState::Option:
			// options menu input
			OptionNavigation();
		default:
			break;
		}
	}
}

// highlight selected option, unhighlight unselected option
void MainMenu::UpdateTextColor(Text* _text, bool highlight)
{
	if (highlight)
	{
		_text->UpdateColor({ 255, 255, 0, 255 });
	}
	else
	{
		_text->UpdateColor({ 255, 255, 255, 255 });
	}
}

// change language 
void MainMenu::ChangeLanguage()
{
	switch (languageIndex)
	{
	case 0:
		GameManager::GetInstance().SetLanguage(GameManager::Language::English);
		break;
	case 1:
		GameManager::GetInstance().SetLanguage(GameManager::Language::Chinese);
		break;
	default:
		break;
	}

	// update window title
	GameManager::GetInstance().SetWindowTitle(TextManager::GetLocalizedText("Space Invaders"));

	// update options menu text after changing language
	optionsText[0]->UpdateText(TextManager::GetLocalizedText("Options"));
	optionsText[1]->UpdateText(TextManager::GetLocalizedText("Language"));
	optionsText[2]->UpdateText(TextManager::GetLocalizedText("English"));
	optionsText[3]->UpdateText(TextManager::GetLocalizedText("Resolution"));
}

// convert resolution from integers to const char for rendering text
const char* MainMenu::ConvertResolution(int width, int height)
{
	resolutionString = std::to_string(width) + " x " + std::to_string(height);

	return resolutionString.c_str();
}

// main menu input
void MainMenu::MenuNavigation()
{
	// select menu
	if (InputManager::GetKeyDown(InputManager::Action::Confirm))
	{
		if (menuIndex == 1)
		{
			UnsetMenu();
			game->SetUpLevel();
		}
		else if (menuIndex == 2)
		{
			SetUpOptions();
		}
		else if (menuIndex == 3)
		{
			SDL_Quit();
		}
		lastMenuChangeTime = SDL_GetTicks();
	}
	// move up
	else if (InputManager::GetKeyDown(InputManager::Action::Up))
	{
		if (menuIndex > 1)
		{
			UpdateTextColor(menuText[menuIndex], false);
			menuIndex--;
			UpdateTextColor(menuText[menuIndex], true);
		}
		lastMenuChangeTime = SDL_GetTicks();
	}
	// move down
	else if (InputManager::GetKeyDown(InputManager::Action::Down))
	{
		if (menuIndex < menuText.size() - 1)
		{
			UpdateTextColor(menuText[menuIndex], false);
			menuIndex++;
			UpdateTextColor(menuText[menuIndex], true);
		}
		lastMenuChangeTime = SDL_GetTicks();
	}
}

// options menu input
void MainMenu::OptionNavigation()
{
	// back to menu
	if (InputManager::GetKeyDown(InputManager::Action::Back))
	{
		UnsetOptions();
		SetUpMenu();

		lastMenuChangeTime = SDL_GetTicks();
	}
	// move up
	else if (InputManager::GetKeyDown(InputManager::Action::Up))
	{
		// options menu
		if (optionIndex > 2)
		{
			UpdateTextColor(optionsText[optionIndex], false);
			optionIndex -= 2;
			UpdateTextColor(optionsText[optionIndex], true);
		}
		lastMenuChangeTime = SDL_GetTicks();
	}
	// move down
	else if (InputManager::GetKeyDown(InputManager::Action::Down))
	{
		if (optionIndex < optionsText.size() - 1)
		{
			UpdateTextColor(optionsText[optionIndex], false);
			optionIndex += 2;
			UpdateTextColor(optionsText[optionIndex], true);
		}
		lastMenuChangeTime = SDL_GetTicks();
	}
	// handle language selection
	else if (InputManager::GetKeyDown(InputManager::Action::Right))
	{
		if (optionIndex == 2 && languageIndex < 1)
		{
			languageIndex++;
			ChangeLanguage();
			lastMenuChangeTime = SDL_GetTicks();
		}
		else if (optionIndex == 4 && resolutionIndex < (sizeof(resolutionTable) / sizeof(resolutionTable[0])) - 1)
		{
			resolutionIndex++;
			GameManager::GetInstance().SetResolution(resolutionTable[resolutionIndex].width, resolutionTable[resolutionIndex].height);
			optionsText[optionIndex]->UpdateText(ConvertResolution(resolutionTable[resolutionIndex].width, resolutionTable[resolutionIndex].height));
			lastMenuChangeTime = SDL_GetTicks();
		}
	}
	else if (InputManager::GetKeyDown(InputManager::Action::Left))
	{
		if (optionIndex == 2 && languageIndex > 0)
		{
			languageIndex--;
			ChangeLanguage();
			lastMenuChangeTime = SDL_GetTicks();
		}
		else if (optionIndex == 4 && resolutionIndex > 0)
		{
			resolutionIndex--;
			GameManager::GetInstance().SetResolution(resolutionTable[resolutionIndex].width, resolutionTable[resolutionIndex].height);
			optionsText[optionIndex]->UpdateText(ConvertResolution(resolutionTable[resolutionIndex].width, resolutionTable[resolutionIndex].height));
			lastMenuChangeTime = SDL_GetTicks();
		}
	}
}
