#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(GameManager::GetInstance().GetRenderer(), tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}

void TextureManager::Render(SDL_Texture* texture, SDL_Rect destRect)
{
	SDL_RenderCopy(GameManager::GetInstance().GetRenderer(), texture, NULL, &destRect);
}
