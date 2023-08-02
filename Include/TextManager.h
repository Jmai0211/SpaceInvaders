#pragma once
#include "SDL_ttf.h"
#include <vector>
#include "GameManager.h"

class Text;

class TextManager
{

public:
	static void Init();
	static void CleanUp();
	static void Render();
	static Text* AddText(int x, int y, const char* text);

	static void UnRegisterText(Text* text);
	static const char* GetLocalizedText(const char* element);

	static TTF_Font* font;

private:
	static std::vector<Text*> textArray;
};