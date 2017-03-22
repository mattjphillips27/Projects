#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameOver.h"
#include "MenuScreen.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <iostream>
#include <math.h>
#include "SplashScreen.h"
#include "DondSplash.h"

//--------------------------------------------------------------------------------------------------

GameScreenManager::GameScreenManager(SCREENS startScreen)
{
	mCurrentScreen = NULL;

	//Ensure the first screen is set up.
	ChangeScreen(startScreen);
}

//--------------------------------------------------------------------------------------------------

GameScreenManager::~GameScreenManager()
{
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::SetMoney(float moneyIn)
{
	cout << "money here" << money << endl;
	cout << "money going in" << moneyIn << endl;

	money = moneyIn;

}

float GameScreenManager::GetMoney()
{
	return money;
}

float GameScreenManager::GetTime()
{
	return gTime;
}

void GameScreenManager::SetTime(float time)
{
	gTime = time;
}


void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen.
	/*if(mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}*/

	GameScreenLevel1* tempScreen1;
	GameScreenLevel2* tempScreen3;
	MenuScreen* tempScreen2;
	GameOver* tempScreen4;
	SplashScreen* tempScreen5;
	DondSplash* tempScreen6;

	//Initialise the new screen.
	switch(newScreen)
	{
		case SCREEN_INTRO:
		break;

		case SCREEN_MENU:
			tempScreen2 = new MenuScreen(this);
			mCurrentScreen = (GameScreen*)tempScreen2;
			tempScreen2 = NULL;
		break;

		case SCREEN_LEVEL1:
			tempScreen1 = new GameScreenLevel1(this);
			mCurrentScreen = (GameScreen*)tempScreen1;
			tempScreen1 = NULL;
		break;
		case SCREEN_LEVEL2:
			tempScreen3 = new GameScreenLevel2(this);
			mCurrentScreen = (GameScreen*)tempScreen3;
			tempScreen3 = NULL;
			break;
		
		case SCREEN_GAMEOVER:
			tempScreen4 = new GameOver(this);
			mCurrentScreen = (GameScreen*)tempScreen4;
			tempScreen4 = NULL;
		break;
		case SCREEN_SPLASH:
			tempScreen5 = new SplashScreen(this);
			mCurrentScreen = (GameScreen*)tempScreen5;
			tempScreen5 = NULL;
			break;
		case SCREEN_SPLASH2:
			tempScreen6 = new DondSplash(this);
			mCurrentScreen = (GameScreen*)tempScreen6;
			tempScreen6 = NULL;
			break;

		case SCREEN_HIGHSCORES:
		break;
		
		default:
		break;
	}
}

//--------------------------------------------------------------------------------------------------