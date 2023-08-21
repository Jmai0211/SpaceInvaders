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
	~TextManager();

	// Initialize TTF system and add fonts to the pool to be used
	static void Init();

	// Sdd fonts to be used
	static void AddFont(std::string id, std::string path, int fontSize);
	// Return the font for adding text
	static TTF_Font* GetFont(std::string id);

	// Render text
	static void Render();

	// Add text to the array
	static void AddText(int x, int y, const char* text, TTF_Font* _font, std::string id);
	// Remove text
	static void UnRegisterText(std::string id);

	// Return the text in the current game language
	static const char* GetLocalizedText(const char* element);

	static std::map<std::string, Text*> textArray;
	static std::vector<std::string> insertionOrder;

private:
	static std::map<std::string, TTF_Font*> fonts;
};