#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>
#include <iostream>
using namespace std;

class Camera;

class GameScreen
{
public:
	GameScreen();
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);


	void OutputLine(float x, float y, string text);


	int money = 0;


	int GetMoney();
	void SetMoney(float money);
	
	

protected:
	SDL_Renderer* mRenderer;

	Camera* mCamera;
};


#endif //_GAMESCREEN_H