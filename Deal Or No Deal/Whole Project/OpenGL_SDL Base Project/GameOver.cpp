#include "GameOver.h"
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
#include "GameScreenLevel1.h"


GameOver::GameOver(GameScreenManager* gsm)
{
	mItems.push_back("Restart");
	mItems.push_back("Exit");
		if (mItems.size() != 0) {
		selected = MENU_RESTART;
	}
	
	gsmanager = gsm;
	
	time = gsmanager->GetTime();

	TimeStr.str(string());
	TimeStr.clear();
	TimeStr << "You lastest :" << time << "seconds" << endl;
}


GameOver::~GameOver()
{

}

void GameOver::Render()
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
	OutputText(45, 80, "Game Over");
	OutputText(45, 70, TimeStr.str());
	int i;
	for (i = 0; i< mItems.size(); i++)
	{
		if (i == selected)
		{
			glColor3f(1.0f, 0.4f, 0.0f);
		}
		else
		{
			glColor3f(0.0, 0.0, 0.0);
		}
		OutputLine(45, 60 - 10 * i, mItems[i]);
	}
	glPopMatrix();
	
	glMatrixMode(GL_MODELVIEW);

	glPopMatrix();

	

}

void GameOver::Update(float deltaTime, SDL_Event e)
{
	HandleInput(e);
}

void GameOver::HandleInput(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (selected > 0)
			{
				selected = selected - 1;
			}
			break;

		case SDLK_DOWN:
			if (selected < mItems.size() - 1)
			{
				selected++;
			}
			break;

		case SDLK_RETURN:
			HandleSelectedItem();
			break;
		}
	}
}

void GameOver::HandleSelectedItem()
{
	if (selected == 0)
	{
		gsmanager->ChangeScreen(SCREEN_MENU);
	}
	else if (selected == 1)
	{
		gsmanager->ChangeScreen(SCREEN_LEVEL1);
	}
}

void GameOver::OutputText(float x, float y, string text)
{

	glRasterPos2f(x, y);  // where to start drawing
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}