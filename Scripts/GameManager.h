#pragma once
#include "SDL.h"
#include <utility>
#include "CommonStructs.h"
#include "Enums.h"

class GameManager
{
public:
	static GameManager& GetInstance();

	// Return game score
	int GetScore() const;
	// Set game score
	void SetScore(int _score);

	// Return game highscore
	int GetHighScore() const;
	// Set game highscore
	void SetHighScore(int _highScore);

	// Return if the game is active
	bool GetActiveGame() const;
	// Set if the game is active
	void SetActiveGame(bool _activeGame);

	// Return current game state
	GameState GetState() const;
	// Set current game state
	void SetState(GameState _state);

	// Return current game language
	Language GetLanguage() const;
	// Set current game language
	void SetLanguage(Language _language);

	// Set the text displayed on the window
	void SetWindowTitle(const char* _title);

	// Return current game resolution
	std::pair<int, int> GetResolution() const;
	// Set current Game resolution
	void SetResolution(int width, int height);

	// Save game settings to a .ini file
	void SaveSettings();
	// Load game settings from a .ini file
	void LoadSettings();

	// Save game data to a .dat file
	void SaveGame();
	// Load game data from a .dat file
	void LoadGame();

private:
	GameManager() = default;
	~GameManager() = default;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	int score;
	int highScore;
	bool activeGame;
	GameState state;
	Language language;

	std::pair<int, int> resolution = std::make_pair(1920, 1080);
};