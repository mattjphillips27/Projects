#ifndef _DonsSPLASH_H
#define _DonsSPLASH_H

#pragma once
#include <vector>
#include <string>
#include "GameScreen.h"
#include "GameScreenManager.h"
#include <sstream>
#include <string>

using namespace std;

class DondSplash : GameScreen
{
public:
	DondSplash(GameScreenManager* gsm);

	~DondSplash();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void OutputText(float x, float y, string text);

	stringstream moneyStr;

	float moneywon = 0;
protected:

	vector<string> mInstructions;
private:

	GameScreenManager* gsmanager;
};
#endif
