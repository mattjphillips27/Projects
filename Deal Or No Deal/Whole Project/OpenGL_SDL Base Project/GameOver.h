#ifndef _GAMEOVER_H
#define _GAMEOVER_H

#include <vector>
#include <string>

#include "GameScreen.h"
#include "GameScreenManager.h"
#include <sstream>


using namespace std;


#define MENU_NONE -1
#define MENU_RESTART 0
#define MENU_EXIT 1

#pragma once
class GameOver : public GameScreen
{
public:
	GameOver(GameScreenManager* gsm);

	~GameOver();
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void OutputText(float x, float y, string text);

	float time;

	stringstream TimeStr;

protected:

	void HandleInput(SDL_Event e);
	vector<string> mItems;
private:
	int selected = MENU_NONE;
	void HandleSelectedItem();
	GameScreenManager* gsmanager;
	

//	stringstream HighScore;

};
#endif

