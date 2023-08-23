#include "AudioManager.h"
#include <iostream>
#include "GameManager.h"

AudioManager::~AudioManager()
{
	Mix_CloseAudio();
}

AudioManager& AudioManager::GetInstance()
{
	static AudioManager instance;
	return instance;
}

void AudioManager::Init()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "Failed to initialize SDL Mixer: " << Mix_GetError() << std::endl;
	}

	SetMusicVolume(volume);
	SetSoundVolume(volume / 5);

	LoadMusic("Assets/Menu.mp3", "BackgroundMusic");
	LoadMusic("Assets/Game.mp3", "GameMusic");
	LoadSoundEffect("Assets/laser2.mp3", "ShootSound");
	LoadSoundEffect("Assets/explosion6.mp3", "ExplodeSound");
}

void AudioManager::SetMusicVolume(int _volume)
{
	if (volume >= 0 && volume <= 128) 
	{
		volume = _volume;
		Mix_VolumeMusic(volume);
		Mix_Volume(-1, volume / 5);
		GameManager::GetInstance().SaveSettings();
	}
}

int AudioManager::GetMusicVolume() const
{
	return volume;
}

void AudioManager::SetSoundVolume(int volume)
{
	//if (volume >= 0 && volume <= 128) 
	//{
	//	soundVolume = volume;
	//	Mix_Volume(-1, soundVolume);
	//}
}

int AudioManager::GetSoundVolume() const
{
	/*return soundVolume;*/
	return 0;
}

bool AudioManager::LoadMusic(const std::string& filePath, const std::string& musicID)
{
	Mix_Music* music = Mix_LoadMUS(filePath.c_str());
	if (!music) 
	{
		std::cout << "Failed to load music: " << filePath << std::endl;
		return false;
	}

	// Load the music track
	loadedMusic.emplace(musicID, music);

	return true;
}

void AudioManager::PlayMusic(const std::string& musicID)
{
	if (Mix_PlayingMusic() == 1)
	{
		Mix_HaltMusic();
	}
	Mix_PlayMusic(loadedMusic[musicID], -1);
}

bool AudioManager::LoadSoundEffect(const std::string& filePath, const std::string& soundID)
{
	Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
	if (!sound) 
	{
		std::cout << "Failed to load sound: " << filePath << std::endl;
	}
	loadedSoundEffects.emplace(soundID, sound);

	return true;
}

void AudioManager::PlaySoundEffect(const std::string& soundID)
{
	Mix_PlayChannel(-1, loadedSoundEffects[soundID], 0);
}

void AudioManager::StopMusic()
{
	Mix_HaltMusic();
}
