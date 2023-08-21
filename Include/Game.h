#pragma once
#include "SDL.h"
#include <iostream>
#include <vector>

class Entity;
class MainMenu;

class Game
{
public:
	// Initialize sub systems
	void Init(const char* title, int xPos, int yPos);

	// Handle input events
	void HandleEvents();

	// Handle main game loop
	void Update();

	// Render all objects
	void Render();

	// Clean up game
	void Clean();

	// Setup gameplay level
	void SetUpLevel();

	// Return to main menu from game
	void BackToMainMenu();

	// Stop the game and display game over message
	static void GameOver();

	// Reset all game data and respawn player and enemies
	void Restart();

	static SDL_Renderer* renderer;
	static SDL_Window* window;

	static MainMenu menu;
	static Entity* player;

private:
	// Spawn player
	void SpawnPlayer();
};