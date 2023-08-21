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

	Text(int x, int y, const char* _text, TTF_Font* _font);
	~Text();

	// Update the content of the text entity
	void UpdateText(const char* _text);
	// Update the color of the text entity
	void UpdateColor(SDL_Color color);
	// Render the text entity
	void render();

	// Update the size of the text entity
	void SetScale(int x, int y);

private:
	TTF_Font* font;
	const char* text;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Color textColor;

	// Generate a texture of the text to be rendered
	void GenerateTexture();
};

