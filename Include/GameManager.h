#pragma once
#include "SDL.h"
#include <utility>
#include "CommonStructs.h"

class GameManager
{
public:
	enum class GameState
	{
		Menu,
		Playing,
		GameOver
	};

	enum class Language
	{
		English,
		Chinese
	};

	static GameManager& GetInstance();

	int GetScore() const;
	void SetScore(int _score);

	bool GetActiveGame() const;
	void SetActiveGame(bool _activeGame);

	GameState GetState() const;
	void SetState(GameState _state);

	Language GetLanguage() const;
	void SetLanguage(Language _language);

	void SetWindowTitle(const char* _title);

	std::pair<int, int> GetResolution() const;
	void SetResolution(int width, int height);

	SDL_Window* GetWindow() const;
	void SetWindow(SDL_Window* _window);

	SDL_Renderer* GetRenderer() const;
	void SetRenderer(SDL_Renderer* _renderer);

	void SaveSettings();
	void LoadSettings();

private:
	GameManager() = default;
	~GameManager() = default;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	static GameManager instance;

	static int score;
	static bool activeGame;
	static GameState state;
	static Language language;

	static std::pair<int, int> resolution;

	static SDL_Window* window;
	static SDL_Renderer* renderer;
};