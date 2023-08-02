#include "TextManager.h"
#include "Game.h"
#include "Text.h"
#include <iostream>

TTF_Font* TextManager::font;
std::vector<Text*> TextManager::textArray;

// initialize font
void TextManager::Init()
{
	if (TTF_Init() < 0)
	{
		std::cout << "Failed to initialize font: " << TTF_GetError() << std::endl;
	}

	font = TTF_OpenFont("Assets/SmileySans-Oblique.ttf", 84);
	if (!font)
	{
		std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
	}
}

// clean up font and text data
void TextManager::CleanUp()
{
	for (Text* text : textArray)
	{
		delete text;
	}
	TTF_CloseFont(font);
	TTF_Quit();
}

// render text
void TextManager::Render()
{
	for (Text* text : textArray)
	{
		text->render();
	}
}

// create new text
Text* TextManager::AddText(int x, int y, const char* text)
{
	Text* newText = new Text(x, y, text);
	textArray.push_back(newText);
	return newText;
}

// remove text
void TextManager::UnRegisterText(Text* text)
{
	std::vector<Text*>::iterator target = std::find(textArray.begin(), textArray.end(), text);
	if (target != textArray.end())
	{
		textArray.erase(target);
	}
	else
	{
		std::cout << "Could not find!" << std::endl;
	}
}

// get the text in the corresponding language
const char* TextManager::GetLocalizedText(const char* element)
{
	for (int i = 0; i < sizeof(textDataTable) / sizeof(textDataTable[0]); i++)
	{
		if (strcmp(textDataTable[i].englishText, element) == 0)
		{
			switch (GameManager::GetInstance().GetLanguage())
			{
			case GameManager::Language::English:
				return textDataTable[i].englishText;
				break;
			case GameManager::Language::Chinese:
				return textDataTable[i].chineseText;
				break;
			default:
				break;
			}
		}
	}

	return nullptr;
}
