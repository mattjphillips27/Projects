#ifndef _GAMESCREENLEVEL3_H
#define _GAMESCREENLEVEL3_H
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
using namespace std;


class Sphere;

class GameScreenLevel3 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel3();
	~GameScreenLevel3();

	
	void		Render();
	void		Update(float deltaTime, SDL_Event e);
	
	void DrawCourt();

	void setLight();
	

	void OutputLine(float x, float y, string text);
	float health = 4;

	
	GameScreenManager* gsmm;

//--------------------------------------------------------------------------------------------------
private:	
	float   mCurrentTime = 0.0;
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


#endif //_GameScreenLevel3_H