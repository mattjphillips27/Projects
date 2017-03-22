#ifndef _AUDIO_H
#define _AUDIO_H
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Constants.h"
#include "Texture2D.h"
#include "GameScreenManager.h"

using namespace::std;


class Audio
{
public:
	Audio(std::string paths);
	~Audio();

	void LoadMusic(std::string path);
	void PlayMusic();
	void PlayPop(string path);
	void musicDone();
	

	Mix_Music* gMusic;
	Mix_Music* mMusic;
	

};

#endif

