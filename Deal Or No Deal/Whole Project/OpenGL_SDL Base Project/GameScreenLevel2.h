#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H
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

class GameScreenLevel2 : GameScreen
{
	//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel2(GameScreenManager* gsm);
	~GameScreenLevel2();


	void Render();
	void Update(float deltaTime, SDL_Event e);

	void DrawCourt();
	void DrawBox();
	void setLight();

	void ThinkingAI(float deltaTime, SDL_Event e);
	void CockyAI(float deltaTime, SDL_Event e);
	void NormalAI(float deltaTime, SDL_Event e);
	void ScaredAI(float deltaTime, SDL_Event e);
	void Dond(float deltaTime, SDL_Event e);
	void Choosing(float deltaTime, SDL_Event e);
	void Final (float deltaTime, SDL_Event e);


	void OutputLine(float x, float y, string text);
	void OutputText(float x, float y, string text);
	float health = 4;

	enum STATE
	{
		THINKING, COCKY, NORMAL, SCARED, DOND, CHOOSING, FINAL
	};

	STATE currentState;
	
	

	GameScreenManager* gsmm;

	//--------------------------------------------------------------------------------------------------

private:
	float   mCurrentTime = 0.0;
	Vector3D position;

	//float money[10];

	int boxes;

	Texture2D* court = new Texture2D();
	Texture2D* denzil = new Texture2D();
	Sphere* playerboundingSphere;
	Object3DS*	m_Denzil;

	float movementY;
	float movementX;
	int score = 25;
	stringstream boxchoice; //The box you choose
	stringstream boxresult;	// what's in the box
	stringstream money;
	stringstream dond;
	string bourbon;

	stringstream offer;
	//stringstream fOffer;
	
	bool selected = false;

	bool NoFinal = false;

	bool firstbox = true;
	float playerBox = 0;
	bool player = false;

	bool first;
	bool second;
	int one;
	int two;
	int result;
	float rotate;
	int round = 0;
	bool rotatef;

	bool thinkingTime = false;

	bool cockyTime = false;
	bool normalTime = false;
	bool scaredTime = false;
	bool finalTime = false;

	float finaloffer = 0;
	float BankersOffer = 0;

	float totalAmountOfMoney;

	float lastFour;
	float divide13;
	float divide23;
	float average;

	float range;

	bool q = true;
	bool w = false;
	bool t = false;
	bool r = false;
	float firstt;
	float secondd;
	float third;
	float fourth;
	
	float smallest= 0;
	float biggest=0;
	float median = 0;
};


#endif //_GameScreenLevel2_H