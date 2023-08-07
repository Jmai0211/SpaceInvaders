#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent() = default;

	SpriteComponent(const char* path)
	{
		SetTexture(path);
	}

	// srcX and src Y are the starting position of the texture in a sprite sheet
	// if your character starts at (0,0), pass in 0 for both srcX and srcY
	// spacing represents the spacing between each animation frame
	// if there are no spacing between each one, you can leave it as 0
	SpriteComponent(const char* path, int srcX, int srcY, int _frames, int _spacing, int _speed)
	{
		animated = true;
		frames = _frames;
		speed = _speed;
		animationStart.x = static_cast<float>(srcX);
		animationStart.y = static_cast<float>(srcY);
		spacing = _spacing;
		SetTexture(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void SetTexture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
		srcRect.x = 0;
		srcRect.y = 0;

		srcRect.w = static_cast<int>(transform->defaultSize.x);
		srcRect.h = static_cast<int>(transform->defaultSize.y);
	}

	void Update() override
	{
		if (animated)
		{
			srcRect.x = static_cast<int>((srcRect.w + spacing) * ((SDL_GetTicks() / speed) % frames));
			srcRect.y = static_cast<int>(animationStart.y);
		}	

		destRect.x = transform->Position.x;
		destRect.y = transform->Position.y;
		destRect.w = transform->Size.x;
		destRect.h = transform->Size.y;
	}

	void Render() override
	{
		TextureManager::Render(texture, srcRect, destRect);
	}

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_FRect destRect;
	Vector2D animationStart;

	bool animated = false;
	int frames = 0;
	int speed = 100;
	int spacing = 0;
};