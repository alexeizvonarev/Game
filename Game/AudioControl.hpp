#pragma once
#include <SDL_mixer.h>
class AudioControl {
public:
	AudioControl(const char* path) {
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
		mus = Mix_LoadMUS(path); //"Data/Audio/Jump.mp3"
	}
	void Play() {
		Mix_PlayMusic(mus, 0);
	}
private:
	Mix_Music* mus;
};