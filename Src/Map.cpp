#include "Map.h"
#include "TextureManager.h"
#include "Game.h"
#include <fstream>
#include <sstream>

Map::Map()
{

}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
    char tile;
    std::fstream mapFile;

    mapFile.open(path);

    for (int y = 0; y < sizeY; y++)
    {
        std::string line;
        std::getline(mapFile, line); // Read the entire line from the file

        std::stringstream ss(line);
        for (int x = 0; x < sizeX; x++)
        {
            int tileValue;
            std::getline(ss, line, ','); // Extract numbers separated by commas
            tileValue = std::stoi(line); // Convert the extracted string to an integer
            Game::AddTile(tileValue, x * 64 + 32, y * 64 + 32);
        }
    }

    mapFile.close();
}
