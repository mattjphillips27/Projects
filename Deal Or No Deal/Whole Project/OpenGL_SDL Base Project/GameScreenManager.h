#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include <SDL.h>
#include <vector>
#include "Commons.h"

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager(SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);


	float money = 0;


	float GetMoney();
	void SetMoney(float money);

	float gTime = 0;

	float GetTime();
	void SetTime(float time);


private:
	GameScreen* mCurrentScreen;
	GameScreenManager* gsm;
};


#endif //_GAMESCREENMANAGER_H