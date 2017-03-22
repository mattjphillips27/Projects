#ifndef _SPLASHSCREEN_H
#define _SPLASHSCREEN_H
#pragma once

#include <vector>
#include <string>

#include "GameScreen.h"
#include "GameScreenManager.h"


class SplashScreen : public GameScreen
{
public:
	SplashScreen(GameScreenManager* gsm);
	~SplashScreen();
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void OutputText(float x, float y, string text);

protected:
	
	vector<string> mInstructions;
private:
	
	GameScreenManager* gsmanager;
};
#endif
