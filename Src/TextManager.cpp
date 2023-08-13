#include "TextManager.h"
#include "Text.h"
#include <iostream>

TTF_Font* TextManager::font;
std::map<std::string, Text*> TextManager::textArray;
std::vector<std::string> TextManager::insertionOrder;

// render text
void TextManager::Render()
{
	for (auto text : textArray)
	{
		text.second->render();
	}
}

// create new text
void TextManager::AddText(int x, int y, const char* text, TTF_Font* _font, std::string id)
{
	Text* newText = new Text(x, y, text, _font);
	textArray.emplace(id, newText);

	insertionOrder.push_back(id);
}

// remove text
void TextManager::UnRegisterText(std::string id)
{
	auto it = textArray.find(id);

	if (it != textArray.end()) {
		// Item found, erase it from the map
		delete it->second; // Clean up the Text object
		textArray.erase(it);
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
