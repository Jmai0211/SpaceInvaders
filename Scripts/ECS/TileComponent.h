#pragma once
#include "ECS.h"
#include "Components.h"
#include <string>
#include "AssetManager.h"
#include "Game.h"

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	TileComponent() = default;

	TileComponent(int srcX, int srcY, int xPos, int yPos, std::string id)
	{
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = 64;
		srcRect.h = 64;

		// Calculate scale based on screen ratio
		std::pair<int, int> resolution = GameManager::GetInstance().GetResolution();
		int screenWidth = resolution.first;
		int screenHeight = resolution.second;

		float widthRatio = static_cast<float>(screenWidth) / 1920.0f;
		float heightRatio = static_cast<float>(screenHeight) / 1080.0f;

		float scale = std::min(widthRatio, heightRatio);

		destRect.x = static_cast<int>(std::round(xPos * scale));
		destRect.y = static_cast<int>(std::round(yPos * scale));
		destRect.w = static_cast<int>(std::round(64 * scale));
		destRect.h = static_cast<int>(std::round(64 * scale));
		
		texture = AssetManager::GetInstance().GetTexture(id);
	}

	void Render() override
	{
		AssetManager::GetInstance().Render(texture, srcRect, destRect);
	}
};