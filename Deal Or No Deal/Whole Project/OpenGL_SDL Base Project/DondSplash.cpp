#include "DondSplash.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "object3DS.h"
#include <iostream>
#include <math.h>
#include <SDL.h>
#include "Camera.h"


DondSplash::DondSplash(GameScreenManager* gsm)
{
	moneywon = gsm->GetMoney();
	//cout << moneywon << endl;

	moneyStr.str(string());
	moneyStr.clear();
	moneyStr <<"$" << moneywon << endl;

	mInstructions.push_back("Congratuations you won: ");
	mInstructions.push_back(moneyStr.str());
	
	gsmanager = gsm;
}


DondSplash::~DondSplash()
{

}

void DondSplash::Render()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int j = 0; j < mInstructions.size(); j++) {
		glColor3f(0.0, 0.0, 0.0);
		OutputText(20, 70 - 10 * j - 10, mInstructions[j]);
	}
	
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void DondSplash::Update(float deltaTime, SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			gsmanager->ChangeScreen(SCREEN_MENU);
			break;
		}
	}
}

void DondSplash::OutputText(float x, float y, string text)
{

	glRasterPos2f(x, y);  // where to start drawing
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}
