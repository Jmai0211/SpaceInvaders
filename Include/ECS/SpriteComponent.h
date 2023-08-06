#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
public:

	SDL_Rect destRect;
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
		srcRect.x = 0;
		srcRect.y = 0;

		destRect.w = static_cast<int>(transform->Size.x);
		destRect.h = static_cast<int>(transform->Size.y);
	}

	void Update() override
	{
		destRect.x = static_cast<int>(transform->Position.x);
		destRect.y = static_cast<int>(transform->Position.y);
		destRect.w = static_cast<int>(transform->Size.x);
		destRect.h = static_cast<int>(transform->Size.y);
	}

	void Render() override
	{
		TextureManager::Render(texture, destRect);
	}

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect;
};