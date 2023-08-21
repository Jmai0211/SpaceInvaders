#pragma once
#include "SDL.h"
#include <utility>
#include "CommonStructs.h"
#include "Enums.h"

class GameManager
{
public:
	static GameManager& GetInstance();

	int GetScore() const;
	void SetScore(int _score);

	int GetHighScore() const;
	void SetHighScore(int _highScore);

	bool GetActiveGame() const;
	void SetActiveGame(bool _activeGame);

	GameState GetState() const;
	void SetState(GameState _state);

	Language GetLanguage() const;
	void SetLanguage(Language _language);

	void SetWindowTitle(const char* _title);

	std::pair<int, int> GetResolution() const;
	void SetResolution(int width, int height);

	void SaveSettings();
	void LoadSettings();

	void SaveGame();
	void LoadGame();

private:
	GameManager() = default;
	~GameManager() = default;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	static int score;
	static int highScore;
	static bool activeGame;
	static GameState state;
	static Language language;

	static std::pair<int, int> resolution;
};