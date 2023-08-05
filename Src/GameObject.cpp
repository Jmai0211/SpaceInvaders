#include "GameObject.h"
#include <iostream>

GameObject::GameObject(const char* textureSheet, const char* bulletTextureSheet, int x, int y)
{
	// Load sprite texture and bullet texture
	//objTexture = TextureManager::LoadTexture(textureSheet, Game::renderer);
	//bulletTexture = TextureManager::LoadTexture(bulletTextureSheet, Game::renderer);

	destRect.x = x;
	destRect.y = y;
	destRect.w = 16;
	destRect.h = 16;

	// Calculate scale based on screen ratio
	std::pair<int, int> resolution = GameManager::GetInstance().GetResolution();
	int screenWidth = resolution.first;
	int screenHeight = resolution.second;

	float widthRatio = static_cast<float>(screenWidth) / 1920.0f;
	float heightRatio = static_cast<float>(screenHeight) / 1080.0f;

	// Take the least of the two ratios
	float scale = std::min(widthRatio, heightRatio);

	// Calculate the scaled size of the object
	float scaledSize = 96 * scale;

	// Calculate the new position with adjusted pivot point
	destRect.x = static_cast<int>(x * widthRatio - (scaledSize / 2));
	destRect.y = static_cast<int>(y * heightRatio - (scaledSize / 2));

	destRect.w = static_cast<int>(96 * scale);
	destRect.h = static_cast<int>(96 * scale);

	bulletDestRect.w = static_cast<int>(32 * scale);
	bulletDestRect.h = static_cast<int>(32 * scale);
}

GameObject::~GameObject()
{
	std::cout << "GameObject destructor called" << std::endl;
	SDL_DestroyTexture(objTexture);
	SDL_DestroyTexture(bulletTexture);
}

// update function
void GameObject::Update()
{
	if (isShotActive)
	{
		// bullet movement
		bulletDestRect.y += bulletDirection * bulletSpeed;

		// handle out of screen logic
		if (bulletDestRect.y < 0 || bulletDestRect.y > 1080 && !isShotActive)
		{
			isShotActive = false;
		}
	}
} 

// render function
void GameObject::Render()
{
	//SDL_RenderCopy(Game::renderer, objTexture, NULL, &destRect);
	//if (isShotActive)
	//{
	//	SDL_RenderCopy(Game::renderer, bulletTexture, NULL, &bulletDestRect);
	//}
}

// movement function
void GameObject::Move()
{
	std::pair<int, int> resolution = GameManager::GetInstance().GetResolution();
	int screenWidth = resolution.first;
	int screenHeight = resolution.second;

	// Calculate the scaling factors for both the X and Y directions based on the new and original resolutions.
	float scaleX = static_cast<float>(screenWidth) / 1920;
	float temp = static_cast<float>(movementSpeed * scaleX);

	destRect.x += static_cast<int>(movementDirection * temp);
}


// shoot function
void GameObject::Shoot()
{
	bulletDestRect.x = destRect.x;
	bulletDestRect.y = destRect.y;
	isShotActive = true;
}

// take damage function
bool GameObject::TakeDamage()
{
	health--;
	if (health <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
