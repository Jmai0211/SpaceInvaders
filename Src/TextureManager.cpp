#include "TextureManager.h"
#include "Game.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}

void TextureManager::Render(SDL_Texture* texture, SDL_Rect srcRect, SDL_FRect destRect)
{
	SDL_RenderCopyF(Game::renderer, texture, &srcRect, &destRect);
}
