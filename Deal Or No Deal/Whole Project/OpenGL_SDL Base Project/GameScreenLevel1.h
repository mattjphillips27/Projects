#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#pragma once


#include "GameScreen.h"
#include "Commons.h"
#include "Constants.h"
#include <windows.h>
#include <GL\gl.h>
#include "../gl/glut.h"
#include <iostream>
#include "object3DS.h"
#include "Texture2D.h"
#include <vector>
#include "Teapot.h"
#include <string>
#include <sstream>
#include <math.h>
#include "Collision.h"
#include "denzil.h"
#include <time.h>
#include <vector>
#include "GameScreenManager.h"
#include "GameOver.h"

using namespace std;


class Sphere;
class GameOver;

class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1(GameScreenManager* gsm);
	~GameScreenLevel1();

	
	void		Render();
	void		Update(float deltaTime, SDL_Event e);
	
	void DrawCourt();

	void setLight();
	

	void OutputLine(float x, float y, string text);
	float health = 4;

	
	GameScreenManager* gsmm;
	float   mCurrentTime = 0.0;
	GameOver* gameover;

	

//--------------------------------------------------------------------------------------------------
private:	
	
	Vector3D position;

	

	Texture2D* court = new Texture2D();
	Texture2D* denzil = new Texture2D();
	Sphere* playerboundingSphere;
	Object3DS*	m_Denzil;
	
	float movementY;
	float movementX;
	int score = 25;
	stringstream ss;
};


#endif //_GAMESCREENLEVEL1_H