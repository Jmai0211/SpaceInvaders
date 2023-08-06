#include "GameManager.h"
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <Game.h>

GameManager GameManager::instance;
int GameManager::score = 0;
bool GameManager::activeGame = false;
GameManager::GameState GameManager::state = GameManager::GameState::Menu;
GameManager::Language GameManager::language = GameManager::Language::English;
std::pair<int, int> GameManager::resolution = std::make_pair(1920, 1080);
// return instance of game manager
GameManager& GameManager::GetInstance()
{
	return instance;
}

// get current score
int GameManager::GetScore() const
{
	return score;
}

// update score
void GameManager::SetScore(int _score)
{
	score = _score;
}

// get if the game is running
bool GameManager::GetActiveGame() const
{
	return activeGame;
}

// update if the game is running
void GameManager::SetActiveGame(bool _activeGame)
{
	activeGame = _activeGame;
}

// get current state of the game
GameManager::GameState GameManager::GetState() const
{
	return state;
}

// update state of the game
void GameManager::SetState(GameState _state)
{
	state = _state;
}

// get current game language
GameManager::Language GameManager::GetLanguage() const
{
	return language;
}

// update game language
void GameManager::SetLanguage(Language _language)
{
	language = _language;

    SaveSettings();
}

void GameManager::SetWindowTitle(const char* _title)
{
    SDL_SetWindowTitle(Game::window, _title);
}

// get current game resolution
std::pair<int, int> GameManager::GetResolution() const
{
	return resolution;
}

// update game resolution
void GameManager::SetResolution(int width, int height)
{
	resolution = std::make_pair(width, height);
	SDL_SetWindowSize(Game::window, resolution.first, resolution.second);

	SDL_SetWindowPosition(Game::window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	SaveSettings();
}

// save game settings to a file
void GameManager::SaveSettings()
{
    // Get the current resolution
    std::pair<int, int> currentResolution = GetInstance().GetResolution();

    // Open the INI file for writing
    std::ofstream file("settings.ini");
    if (!file.is_open())
    {
        // Failed to open the INI file
        std::cout << "Failed to open 'settings.ini' for writing." << std::endl;
    }

    // Write the language and resolution values to the INI file
    file << "[Settings]\n";
    file << "Language=" << static_cast<int>(GetInstance().GetLanguage()) << "\n";
    file << "Width=" << currentResolution.first << "\n";
    file << "Height=" << currentResolution.second << "\n";

    // Close the file
    file.close();

	std::cout << "Settings successfully saves." << std::endl;
}

// load game settings from file
void GameManager::LoadSettings()
{    
    // Open the INI file for reading
    std::ifstream file("settings.ini");
    if (!file.is_open())
    {
        // Failed to open the INI file
        std::cerr << "Failed to open 'settings.ini' for reading." << std::endl;
    }

    // Variables to store the loaded settings
    int language = 0;
    int width = 800;
    int height = 600;

    // Read the settings from the INI file
    std::string line;
    while (std::getline(file, line))
    {
        if (line.find("Language=") != std::string::npos)
        {
            language = std::stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("Width=") != std::string::npos)
        {
            width = std::stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("Height=") != std::string::npos)
        {
            height = std::stoi(line.substr(line.find("=") + 1));
        }
    }

    // Close the file
    file.close();

    // Set the loaded settings in the game manager
    GameManager::GetInstance().SetLanguage(static_cast<GameManager::Language>(language));
    GameManager::GetInstance().SetResolution(width, height);
}
