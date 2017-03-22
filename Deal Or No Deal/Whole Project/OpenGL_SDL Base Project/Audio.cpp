#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Audio.h"
using namespace::std;

Audio::Audio(string paths)
{
	gMusic = NULL;
	
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Mixer could not initialise. error: " << Mix_GetError();
	}

	LoadMusic(paths);
	PlayMusic();
}

Audio::~Audio()
{
	/*Mix_FreeMusic( gMusic );
    gMusic = NULL;*/
}

void Audio::LoadMusic(string path)
{

	gMusic = Mix_LoadMUS(path.c_str());
	
	if(gMusic == NULL)
	{
		cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	}
	
}

void Audio::PlayMusic()
{
	if(Mix_PlayingMusic() == 0)
    {
		Mix_PlayMusic(gMusic, 0);
	}
}

void Audio::PlayPop(string path)
{
	mMusic = Mix_LoadMUS(path.c_str());

	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(mMusic, 0);
	}
}


