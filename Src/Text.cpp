#include "Text.h"
#include "Game.h"
#include "TextManager.h"
#include "GameManager.h"

Text::Text(int x, int y, const char* _text)
{
	xPos = x;
	yPos = y;

	xScale = 1;
	yScale = 1;

	text = _text;

	textColor = { 255, 255, 255, 255 };

	texture = NULL;
	surface = NULL;
	GenerateTexture();
}

Text::~Text()
{
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TextManager::UnRegisterText(this);
}

// create text texture
void Text::GenerateTexture()
{
	if (surface != NULL)
	{
		SDL_FreeSurface(surface);
		surface = NULL; // Set to NULL after freeing to avoid double deletion
	}
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL; // Set to NULL after freeing to avoid double deletion
	}

	surface = TTF_RenderUTF8_Blended(TextManager::font, text, textColor);
	if (surface == NULL)
	{
		std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
	}

	texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
}

// update text with new text
void Text::UpdateText(const char* _text)
{
	text = _text;

	GenerateTexture();
}

// update the color of the text
void Text::UpdateColor(SDL_Color color)
{
	textColor = color;

	GenerateTexture();
}

// render this text
void Text::render()
{    
	// Get the current game resolution
	std::pair<int, int> resolution = GameManager::GetInstance().GetResolution();
	int screenWidth = resolution.first;
	int screenHeight = resolution.second;

	// Calculate the scaling factor for both X and Y directions based on the original resolution (1920x1080)
	float scaleX = static_cast<float>(screenWidth) / 1920;
	float scaleY = static_cast<float>(screenHeight) / 1080;

	// Calculate the scaled X and Y positions based on the scaling factor
	int scaledXPos = static_cast<int>(xPos * scaleX);
	int scaledYPos = static_cast<int>(yPos * scaleY);

	// Calculate the scaled width and height
	int scaledWidth = static_cast<int>(surface->w * xScale * scaleX);
	int scaledHeight = static_cast<int>(surface->h * yScale * scaleY);

	// Adjust the position using the pivot point
	int pivotX = scaledXPos - (scaledWidth / 2); // Use the X pivot point (e.g., left side)
	int pivotY = scaledYPos - (scaledHeight / 2); // Use the Y pivot point (e.g., top side)

	// Set the destination rectangle
	SDL_Rect destRect;
	destRect.x = pivotX;
	destRect.y = pivotY;
	destRect.w = scaledWidth;
	destRect.h = scaledHeight;

	// Render the text
	SDL_RenderCopy(Game::renderer, texture, NULL, &destRect);
}

// update the scale of the text
void Text::SetScale(int x, int y)
{
	xScale = x;
	yScale = y;
}
