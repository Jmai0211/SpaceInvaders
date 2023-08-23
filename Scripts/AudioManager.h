#pragma once
#include "SDL.h"
#include "SDL_mixer.h"
#include <string>
#include <map>

class AudioManager
{
public:
	static AudioManager& GetInstance();

	// Initialize audio manager and play first music
	void Init();

	// Set music volume
	void SetMusicVolume(int _volume);
	// Return music volume
	int GetMusicVolume() const;

	// Set sound volume
	void SetSoundVolume(int _volume);
	// Return sound volume
	int GetSoundVolume() const;

	// Load music from path and assign it an ID
	bool LoadMusic(const std::string& filePath, const std::string& musicID);

	// Play music with ID
	void PlayMusic(const std::string& musicID);

	// Load sound from path and assign it an ID
	bool LoadSoundEffect(const std::string& filePath, const std::string& soundID);

	// Play sound with ID
	void PlaySoundEffect(const std::string& soundID);

	// Stop current playing music
	void StopMusic();

private:
	AudioManager() = default;
	~AudioManager();
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;

	int volume;

	std::map<std::string, Mix_Music*> loadedMusic;
	std::map<std::string, Mix_Chunk*> loadedSoundEffects;
};