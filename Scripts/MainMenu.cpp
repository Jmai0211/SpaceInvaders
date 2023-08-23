#include "MainMenu.h"
#include "GameManager.h"
#include "Game.h"
#include <string>
#include "CommonStructs.h"
#include "AssetManager.h"
#include "AudioManager.h"

Game* MainMenu::game;

const char* languageText;

// setup main menu
void MainMenu::SetUpMenu()
{
	GameManager::GetInstance().SetState(GameState::Menu);
	menuIndex = 1;
	TextManager::AddText(960, 230, TextManager::GetLocalizedText("Space Invaders"), TextManager::GetFont("Large"), "Title");

	TextManager::AddText(960, 500, TextManager::GetLocalizedText("Start Game"), TextManager::GetFont("Normal"), "StartGame");
	TextManager::AddText(960, 700, TextManager::GetLocalizedText("Options"), TextManager::GetFont("Normal"), "Options");
	TextManager::AddText(960, 900, TextManager::GetLocalizedText("Exit Game"), TextManager::GetFont("Normal"), "ExitGame");

	TextManager::textArray["StartGame"]->UpdateColor({ 255, 255, 0, 255 });

	AudioManager::GetInstance().PlayMusic("BackgroundMusic");
}

void MainMenu::MenuConfirm()
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
}

void MainMenu::MenuUp()
{
	if (menuIndex > 1)
	{
		std::string id = TextManager::insertionOrder[menuIndex];
		auto it = TextManager::textArray.find(id);
		if (it != TextManager::textArray.end())
		{
			it->second->UpdateColor({ 255, 255, 255, 255 });
		}

		// Increase the menuIndex
		menuIndex--;

		id = TextManager::insertionOrder[menuIndex];
		it = TextManager::textArray.find(id);
		if (it != TextManager::textArray.end())
		{
			it->second->UpdateColor({ 255, 255, 0, 255 });
		}
	}
}

void MainMenu::MenuDown()
{
	if (menuIndex < TextManager::insertionOrder.size() - 1)
	{
		std::string id = TextManager::insertionOrder[menuIndex];
		auto it = TextManager::textArray.find(id);
		if (it != TextManager::textArray.end())
		{
			it->second->UpdateColor({ 255, 255, 255, 255 });
		}

		// Increase the menuIndex
		menuIndex++;

		id = TextManager::insertionOrder[menuIndex];
		it = TextManager::textArray.find(id);
		if (it != TextManager::textArray.end())
		{
			it->second->UpdateColor({ 255, 255, 0, 255 });
		}
	}
}

void MainMenu::OptionBack()
{
	UnsetOptions();
	SetUpMenu();
}

void MainMenu::OptionLeft()
{
	if (optionIndex == 2 && languageIndex > 0)
	{
		languageIndex--;
		ChangeLanguage();
	}
	else if (optionIndex == 4 && resolutionIndex > 0)
	{
		resolutionIndex--;
		GameManager::GetInstance().SetResolution(resolutionTable[resolutionIndex].width, resolutionTable[resolutionIndex].height);
		TextManager::textArray["Resolution"]->UpdateText(ConvertResolution(resolutionTable[resolutionIndex].width, resolutionTable[resolutionIndex].height));
	}
	else if (optionIndex == 6 && AudioManager::GetInstance().GetMusicVolume() > 0)
	{
		AudioManager::GetInstance().SetMusicVolume(AudioManager::GetInstance().GetMusicVolume() - 1);
		TextManager::textArray["Volume"]->UpdateText(ConvertVolume(AudioManager::GetInstance().GetMusicVolume()));
	}
}

void MainMenu::OptionRight()
{
	if (optionIndex == 2 && languageIndex < 1)
	{
		languageIndex++;
		ChangeLanguage();
	}
	else if (optionIndex == 4 && resolutionIndex < (sizeof(resolutionTable) / sizeof(resolutionTable[0])) - 1)
	{
		resolutionIndex++;
		GameManager::GetInstance().SetResolution(resolutionTable[resolutionIndex].width, resolutionTable[resolutionIndex].height);
		TextManager::textArray["Resolution"]->UpdateText(ConvertResolution(resolutionTable[resolutionIndex].width, resolutionTable[resolutionIndex].height));
	}
	else if (optionIndex == 6 && AudioManager::GetInstance().GetMusicVolume() < 128)
	{
		AudioManager::GetInstance().SetMusicVolume(AudioManager::GetInstance().GetMusicVolume() + 1);
		TextManager::textArray["Volume"]->UpdateText(ConvertVolume(AudioManager::GetInstance().GetMusicVolume()));
	}
}

void MainMenu::OptionUp()
{
	if (optionIndex > 2)
	{
		std::string id = TextManager::insertionOrder[optionIndex];
		auto it = TextManager::textArray.find(id);
		if (it != TextManager::textArray.end())
		{
			it->second->UpdateColor({ 255, 255, 255, 255 });
		}

		// Increase the menuIndex
		optionIndex -= 2;

		id = TextManager::insertionOrder[optionIndex];
		it = TextManager::textArray.find(id);
		if (it != TextManager::textArray.end())
		{
			it->second->UpdateColor({ 255, 255, 0, 255 });
		}
	}
}

void MainMenu::OptionDown()
{
	if (optionIndex < TextManager::textArray.size() - 1)
	{
		std::string id = TextManager::insertionOrder[optionIndex];
		auto it = TextManager::textArray.find(id);
		if (it != TextManager::textArray.end())
		{
			it->second->UpdateColor({ 255, 255, 255, 255 });
		}

		// Increase the menuIndex
		optionIndex += 2;

		id = TextManager::insertionOrder[optionIndex];
		it = TextManager::textArray.find(id);
		if (it != TextManager::textArray.end())
		{
			it->second->UpdateColor({ 255, 255, 0, 255 });
		}
	}
}

// setup options menu
void MainMenu::SetUpOptions()
{
	GameManager::GetInstance().SetState(GameState::Option);
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

	TextManager::AddText(960, 230, TextManager::GetLocalizedText("Options"), TextManager::GetFont("Large"), "OptionsTitle");

	TextManager::AddText(650, 500, TextManager::GetLocalizedText("Language"), TextManager::GetFont("Normal"), "LanguageTitle");
	TextManager::AddText(1250, 500, TextManager::GetLocalizedText("English"), TextManager::GetFont("Normal"), "Language");

	TextManager::AddText(650, 700, TextManager::GetLocalizedText("Resolution"), TextManager::GetFont("Normal"), "ResolutionTitle");
	TextManager::AddText(1250, 700, ConvertResolution(GameManager::GetInstance().GetResolution().first, GameManager::GetInstance().GetResolution().second), TextManager::GetFont("Normal"), "Resolution");
	
	TextManager::AddText(650, 900, TextManager::GetLocalizedText("Volume"), TextManager::GetFont("Normal"), "VolumeTitle");
	TextManager::AddText(1250, 900, ConvertVolume(AudioManager::GetInstance().GetMusicVolume()), TextManager::GetFont("Normal"), "Volume");

	TextManager::textArray["Language"]->UpdateColor({ 255, 255, 0, 255 });
}

// clear options list to avoid memory leak / unnecessary memory usage
void MainMenu::UnsetOptions()
{
	TextManager::UnRegisterText("OptionsTitle");
	TextManager::UnRegisterText("LanguageTitle");
	TextManager::UnRegisterText("Language");
	TextManager::UnRegisterText("ResolutionTitle");
	TextManager::UnRegisterText("Resolution");
	TextManager::UnRegisterText("VolumeTitle");
	TextManager::UnRegisterText("Volume");
	TextManager::insertionOrder.clear();
}

// clear menu list to avoid memory leak / unnecessary memory usage
void MainMenu::UnsetMenu()
{
	TextManager::UnRegisterText("Title");
	TextManager::UnRegisterText("StartGame");
	TextManager::UnRegisterText("Options");
	TextManager::UnRegisterText("ExitGame");
	TextManager::insertionOrder.clear();
}

// change language 
void MainMenu::ChangeLanguage()
{
	switch (languageIndex)
	{
	case 0:
		GameManager::GetInstance().SetLanguage(Language::English);
		break;
	case 1:
		GameManager::GetInstance().SetLanguage(Language::Chinese);
		break;
	default:
		break;
	}

	// update window title
	GameManager::GetInstance().SetWindowTitle(TextManager::GetLocalizedText("Space Invaders"));

	// update options menu text after changing language
	TextManager::textArray["OptionsTitle"]->UpdateText(TextManager::GetLocalizedText("Options"));
	TextManager::textArray["LanguageTitle"]->UpdateText(TextManager::GetLocalizedText("Language"));
	TextManager::textArray["Language"]->UpdateText(TextManager::GetLocalizedText("English"));
	TextManager::textArray["ResolutionTitle"]->UpdateText(TextManager::GetLocalizedText("Resolution"));
	TextManager::textArray["VolumeTitle"]->UpdateText(TextManager::GetLocalizedText("Volume"));
}

// convert resolution from integers to const char for rendering text
const char* MainMenu::ConvertResolution(int width, int height)
{
	resolutionString = std::to_string(width) + " x " + std::to_string(height);

	return resolutionString.c_str();
}

const char* MainMenu::ConvertVolume(int volume)
{
	volumeString = std::to_string(volume);
	return volumeString.c_str();
}
