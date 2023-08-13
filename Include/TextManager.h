#pragma once
#include "SDL_ttf.h"
#include <vector>
#include <string>
#include <map>
#include "GameManager.h"

class Text;

class TextManager
{
public:
	static void Render();
	static void AddText(int x, int y, const char* text, TTF_Font* _font, std::string id);

	static void UnRegisterText(std::string id);
	static const char* GetLocalizedText(const char* element);

	static TTF_Font* font;
	static std::map<std::string, Text*> textArray;
	static std::vector<std::string> insertionOrder;

private:
};