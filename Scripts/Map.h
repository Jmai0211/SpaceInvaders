#pragma once
#include "Game.h"
#include <string>

class Map
{
public:
	Map();
	~Map();

	// Load map from a text file
	static void LoadMap(std::string path, int sizeX, int sizeY);

private:
	// Create tile based on the loaded map
	static void AddTile(int srcX, int srcY, int xPos, int yPos);
};