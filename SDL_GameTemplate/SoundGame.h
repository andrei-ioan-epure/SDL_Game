#pragma once
#include<SDL.h>
#include<SDL_mixer.h>
#include<vector>
class SoundGame {
private:
	std::vector<Mix_Chunk*> mSoundEffectBank;

public:
	SoundGame();
	~SoundGame();

	void addSound(const char* path);

	void playSound(const int which) const;
	void stopSound(const int which) const;

};