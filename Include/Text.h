#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

class Text
{
public:
	int xPos;
	int yPos;
	int xScale;
	int yScale;

	Text(int x, int y, const char* _text);
	~Text();
	void GenerateTexture();

	void UpdateText(const char* _text);
	void UpdateColor(SDL_Color color);
	void render();

	void SetScale(int x, int y);

private:
	const char* text;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Color textColor;
};

