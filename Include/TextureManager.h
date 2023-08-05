#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "GameManager.h"

class TextureManager 
{
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Render(SDL_Texture* texture, SDL_Rect destRect);
};