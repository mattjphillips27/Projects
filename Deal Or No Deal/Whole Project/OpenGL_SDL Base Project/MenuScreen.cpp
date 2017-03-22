#include "MenuScreen.h"
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



MenuScreen::MenuScreen(GameScreenManager* gsm)
{
	mMenuItems.push_back("Level 1");
	mMenuItems.push_back("Level 2");
	mMenuItems.push_back("Exit");
	if (mMenuItems.size() != 0) 
	{
		selected = MENU_LEVEL1;
	}
	mInstructions.push_back("Use arrow keys to navigate menu");
	mInstructions.push_back("Enter to select");
	mInstructions.push_back("WASD to control Denzil");
	

	plop = gsm;

	
}

MenuScreen::~MenuScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	delete this;
}

void MenuScreen::Render() 
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

	int i;
	for (i = 0; i< mMenuItems.size(); i++) 
	{
		if (i == selected) 
		{
			glColor3f(1.0f, 0.4f, 0.0f);
		}
		else 
		{
			glColor3f(0.0, 0.0, 0.0);
		}
		OutputLine(30, 80 - 10 * i, mMenuItems[i]);
	}
	for (int j = 0; j < mInstructions.size(); j++) {
		glColor3f(0.0, 0.0, 0.0);
		OutputLine(20, 70 - 10 * j - 10 * i, mInstructions[j]);
	}

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}

void MenuScreen::Update(float deltaTime, SDL_Event e) 
{
	HandleInput(e);
}

void MenuScreen::HandleInput(SDL_Event e)
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
				if (selected < mMenuItems.size() - 1)
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

void MenuScreen::HandleSelectedItem()
{
	if (selected == 0)
	{
		plop->ChangeScreen(SCREEN_LEVEL1);
	}
	else if (selected == 1)
	{
		plop->ChangeScreen(SCREEN_SPLASH);
	}
}

