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
    std::fstream mapFile;

    mapFile.open(path);

    for (int y = 0; y < sizeY; y++)
    {
        std::string line;
        std::getline(mapFile, line);

        std::stringstream ss(line);
        for (int x = 0; x < sizeX; x++)
        {
            // read the file and get the tile index of the sprite
            int tileValue;
            std::getline(ss, line, ',');
            tileValue = std::stoi(line) - 1;

            // convert the tile index into src rects to be rendered
            int numColumns = 2560 / 64;
            int numRows = 2304 / 64;

            int rowIndex = tileValue / numRows;
            int columnIndex = tileValue % numColumns;

            int tileX = columnIndex * 64;
            int tileY = rowIndex * 64;

            Game::AddTile(tileX, tileY, x * 64, y * 64);
        }
    }

    mapFile.close();
}
