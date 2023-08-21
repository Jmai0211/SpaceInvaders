#include "TextManager.h"
#include "Text.h"
#include <iostream>

std::map<std::string, TTF_Font*> TextManager::fonts;
std::map<std::string, Text*> TextManager::textArray;
std::vector<std::string> TextManager::insertionOrder;

TextManager::~TextManager()
{
	for (auto f : fonts)
	{
		TTF_CloseFont(f.second);
	}
	fonts.clear();
	TTF_Quit();
}

void TextManager::Init()
{
	if (TTF_Init() == -1)
	{
		std::cout << "Failed to initialize Fonts: " << TTF_GetError() << std::endl;
	}
	else
	{
		AddFont("Small", "Assets/SmileySans-Oblique.ttf", 60);
		AddFont("Normal", "Assets/SmileySans-Oblique.ttf", 96);
		AddFont("Large", "Assets/SmileySans-Oblique.ttf", 144);
	}
}

void TextManager::AddFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* TextManager::GetFont(std::string id)
{
	return fonts[id];
}

void TextManager::Render()
{
	for (auto text : textArray)
	{
		text.second->render();
	}
}

void TextManager::AddText(int x, int y, const char* text, TTF_Font* _font, std::string id)
{
	Text* newText = new Text(x, y, text, _font);
	textArray.emplace(id, newText);

	insertionOrder.push_back(id);
}

void TextManager::UnRegisterText(std::string id)
{
	auto it = textArray.find(id);

	if (it != textArray.end()) {
		delete it->second;
		textArray.erase(it);
	}
}

const char* TextManager::GetLocalizedText(const char* element)
{
	for (int i = 0; i < sizeof(textDataTable) / sizeof(textDataTable[0]); i++)
	{
		if (strcmp(textDataTable[i].englishText, element) == 0)
		{
			switch (GameManager::GetInstance().GetLanguage())
			{
			case Language::English:
				return textDataTable[i].englishText;
				break;
			case Language::Chinese:
				return textDataTable[i].chineseText;
				break;
			default:
				break;
			}
		}
	}

	return nullptr;
}
