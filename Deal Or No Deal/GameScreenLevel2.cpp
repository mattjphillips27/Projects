#include "GameScreenLevel2.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "object3DS.h"
#include <iostream>
#include <math.h>
#include <vector>
#include "Collision.h"
#include "Audio.h"
#include "Box.h"

#include <algorithm>


using namespace::std;


vector<Box*> theBoxes;

float a[22] = { 0.01, 0.1, 0.5, 1, 5, 10, 50, 100, 250, 500, 750, 1000, 3000, 5000, 10000, 15000, 20000, 35000, 50000, 75000, 100000, 250000 };
float b[22] = { 0.01, 0.1, 0.5, 1, 5, 10, 50, 100, 250, 500, 750, 1000, 3000, 5000, 10000, 15000, 20000, 35000, 50000, 75000, 100000, 250000 };

string back[22] = { "0.01", "0.1", "0.5", "1", "5", "10", "50", "100", "250", "500", "750", "1000", "3000", "5000", "10000", "15000", "20000", "35000", "50000", "75000", "100000", "250000" };

//--------------------------------------------------------------------------------------------------

GameScreenLevel2::GameScreenLevel2(GameScreenManager* gsm) : GameScreen()
{
	gsmm = gsm;
	boxes = 10;

	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(90.0f, aspect, 0.1f, 1000.0f);
	
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//court->Load("court.raw", 512, 512);
	denzil->Load("bo1x.bmp", 1024, 1024);

	m_Denzil = new Object3DS(Vector3D(0.0f, 0.0f, 0.0f), "box1.3ds");

	rotatef = false;
	
	rotate = 0.0;
	random_shuffle(&a[0], &a[22]);
	//random_shuffle(&b[0], &b[22]);

	/*for (unsigned i = 0; i < 10; i++)
	{
		cout << a[i];
	}
	cout << endl;*/



	for (int i = 0; i < 22; i++)
	{

		glBindTexture(GL_TEXTURE_2D, denzil->GetID());
		theBoxes.push_back(new Box(a[i]));
	}




	totalAmountOfMoney = 0;
	for (int b = 0; b < theBoxes.size(); b++)
	{
		totalAmountOfMoney += a[b];
	}
	cout << totalAmountOfMoney << endl;


	currentState = CHOOSING;
}

//--------------------------------------------------------------------------------------------------

GameScreenLevel2::~GameScreenLevel2()
{
	
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel2::DrawCourt()
{
	//glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, court->GetID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 10, -10.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, -10.0, -10.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, -10.0, 10.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 10.0, 10.0);
	glEnd();
	//glDisable(GL_TEXTURE_2D);
}

void GameScreenLevel2::DrawBox()
{
	
	glBindTexture(GL_TEXTURE_2D, denzil->GetID());
	m_Denzil->render();
}

void GameScreenLevel2::setLight() {
	float light_pos[] = { 1.0, 1.0, 1.0, 50.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}


void GameScreenLevel2::OutputLine(float x, float y, string text)
{
	
	glRasterPos2f(x, y);  // where to start drawing
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}

void GameScreenLevel2::OutputText(float x, float y, string text)
{
	
	glRasterPos2f(x, y);  // where to start drawing
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}

void GameScreenLevel2::Render()
{
	glColor3f(1.0, 1.0, 1.0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	GameScreen::Render();

	glPushMatrix();
	selected = false;
		glTranslatef(8.0, -5.0f, 0.0f);
			glPushMatrix();
				glRotatef(-90, 0.0, 1.0, 0.0);
				
					for (int i = 0; i< theBoxes.size(); i++)
					{
						//cout << "Render 1: " << bourbon << endl;
						if (bourbon == back[i])
						{
							glColor3f(1.0f, 0.4f, 0.0f);
							back[i] = " ";
						}
						else
						{
							glColor3f(1.0, 0.0, 8.0);


						}
						OutputText(-10, 0.5 * i, back[i]);
					}
			glPopMatrix();
			glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glTranslatef(0.0, 0.0f, -50.0f);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(-45, 0.0, 1.0, 0.0);
	


	
	
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(60.0, 20.0f, 0.0f);
	glPushMatrix();
	
	for (int i = 0; i < theBoxes.size(); i++)
	{
		glTranslatef(-20.0, 0.0f, 0.0f);
		OutputLine(10, 5, std::to_string(i));
		theBoxes[i]->Render();
		

		if (i == 4)
		{
			glTranslatef(100.0, -35.0f, 0.0f);
		}
		if (i == 9)
		{
			glTranslatef(100.0, -35.0f, 0.0f);
		}
		if (i == 14)
		{
			glTranslatef(100.0, -35.0f, 0.0f);
		}
		if (i == 19)
		{
			glTranslatef(70.0, -35.0f, 0.0f);
		}
	}
	glPopMatrix();

	if (player)
	{
		glPushMatrix();
			glRotatef(90, 1.0, 0.0, 0.0);
			glRotatef(-90, 1.0, 0.0, 0.0);
			glTranslatef(0.0, 0.0f, 0.0f);
			glScalef(0.5, 0.5, 0.5);
			DrawBox();
		glPopMatrix();
	}

	/*glPushMatrix();
	glTranslatef(0.0, 0.0f, -15.0f);
	DrawCourt();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0f, 5.0f);
	glRotatef(180, 1.0, 0.0, 0.0);
	DrawCourt();
	glPopMatrix();*/

	// first render the teapot, then

	glColor3f(8.0, 0.0, 8.0);

	glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, 100, 0, 100);
		OutputLine(5, 95, boxchoice.str());
		
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	OutputLine(5, 90, boxresult.str());
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	OutputLine(5, 5, offer.str());
	OutputLine(30, 5, dond.str());
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();



	



	

	glDisable(GL_TEXTURE_2D);

}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	GameScreen::Update(deltaTime, e);
	// Call Teapot update
	for (int i = 0; i < theBoxes.size(); i++)
	{
		theBoxes[i]->Update(deltaTime, e);
	}

	switch (currentState)
	{
	case GameScreenLevel2::THINKING:
		ThinkingAI(deltaTime, e);
		break;
	case GameScreenLevel2::COCKY:
		CockyAI(deltaTime, e);
		break;
	case GameScreenLevel2::NORMAL:
		NormalAI(deltaTime, e);
		break;

	case GameScreenLevel2::SCARED:
		ScaredAI(deltaTime, e);
		break;
	case GameScreenLevel2::DOND:
		Dond(deltaTime, e);
		break;
	case GameScreenLevel2::CHOOSING:
		Choosing( deltaTime, e);
		break;
	case GameScreenLevel2::FINAL:
		Final(deltaTime, e);
		break;
	}

	
	
	
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_1:
				if (first == true)
				{
					two = 1;
					second = true;
				}
				else
				{ 
					one = 1;
					first = true;
				}

			break;

			case SDLK_2:
				if (first == true)
				{
					two = 2;
					second = true;
				}
				else
				{
					one = 2;
					first = true;
				}
			break;

			case SDLK_3:
				if (first == true)
				{
					two = 3;
					second = true;
				}
				else
				{
					one = 3;
					first = true;
				}
			break;

			case SDLK_4:
				if (first == true)
				{
					two = 4;
					second = true;
				}
				else
				{
					one = 4;
					first = true;
				}
			break;

			case SDLK_5:
				if (first == true)
				{
					two = 5;
					second = true;
				}
				else
				{
					one = 5;
					first = true;
				}
			break;

			case SDLK_6:
				if (first == true)
				{
					two = 6;
					second = true;
				}
				else
				{
					one = 6;
					first = true;
				}
			break;

			case SDLK_7:
				if (first == true)
				{
					two = 7;
					second = true;
				}
				else
				{
					one = 7;
					first = true;
				}
			break;

			case SDLK_8:
				if (first == true)
				{
					two = 8;
					second = true;
				}
				else
				{
					one = 8;
					first = true;
				}
			break;

			case SDLK_9:
				if (first == true)
				{
					two = 9;
					second = true;
				}
				else
				{
					one = 9;
					first = true;
				}
			break;

			case SDLK_0:
					if (first == true)
					{
						two = 0;
						second = true;
					}
					else
					{
						one = 0;
						first = true;
					}
			break;
		}
	}
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel2::ThinkingAI(float deltaTime, SDL_Event e)
{
	if (thinkingTime == false)
	{
		average = 0;
		for (int b = 0; b < theBoxes.size(); b++)
		{
			average += a[b];
		}

		lastFour = firstt + secondd + third + fourth;

		average = average / 22;

		divide13 = average / 3;
		divide23 = divide13 * 2;

		
		int intArray[22];

		for (int m = 0; m < 22; m++)
		{
			intArray[m] = a[m];
		}

		//Now we call the sort function
		sort(intArray, intArray + 22);


		for (int i = 1; i< theBoxes.size(); i++)
		{
			smallest = intArray[11];
			biggest = intArray[12];
		}

		cout << smallest << " " << biggest << endl;

		median = (smallest + biggest) / 2;

		cout << median << endl;
		

		cout << " Average: " << average  << endl;
		cout << " Last Four: " << lastFour << endl;
		cout << "I'm CockyAI, I offer you :" << average / 3 << endl;
		cout << "I'm NormalAI, I offer you :" << median * 10 << endl;
		cout << "I'm ScaredAI, I offer you :" << average << endl;
		cout << " Average / 3: " << average / 3 << endl;

		if (lastFour > divide23)
		{
			currentState = COCKY;
			cockyTime = true;
		}

		else if (lastFour < divide13)
		{
			currentState = SCARED;
			scaredTime = true;
		}

		else
		{
			currentState = NORMAL;
			normalTime = true;
		}

		thinkingTime = true;

	}
}

void GameScreenLevel2::CockyAI(float deltaTime, SDL_Event e)
{
	if (cockyTime)
	{
		cout << "I am Cocky" << endl;
	//	cout << "I offer you :" << average / 3 << endl;
		cockyTime = false;

		offer.str(string());
		offer.clear();
		offer << "I offer you $" << average / 3 << endl;
		BankersOffer = average / 3;
		currentState = DOND;
	}
}

void GameScreenLevel2::NormalAI(float deltaTime, SDL_Event e)
{
	if (normalTime)
	{
		cout << "I am Normal" << endl;
		normalTime = false;
		//cout << "I offer you :" << average / 3 << endl;

		offer.str(string());
		offer.clear();
		offer << "I offer you $" << median * 10 << endl;
		BankersOffer = median * 10;

		currentState = DOND;
	}
	
}

void GameScreenLevel2::ScaredAI(float deltaTime, SDL_Event e)
{
	if (scaredTime)
	{
		cout << "I am Scared" << endl;
		scaredTime = false;

		offer.str(string());
		offer.clear();
		offer << "I offer you $" << average << endl;
		BankersOffer = average;

		currentState = DOND;
	}
}

void GameScreenLevel2::Dond(float deltaTime, SDL_Event e)
{
	dond.str(string());
	dond.clear();
	dond << "Deal Or No Deal? " << endl;
	//cout << BankersOffer << endl;

	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_y:
			//GAME OVER
			//SetMoney(BankersOffer);
			gsmm->SetMoney(BankersOffer);
			gsmm->ChangeScreen(SCREEN_SPLASH2);

		break;
		case SDLK_n:
			if (NoFinal)
			{
				gsmm->SetMoney(playerBox);
				gsmm->ChangeScreen(SCREEN_SPLASH2);
			}
			else
			{
				dond.str(string());
				dond.clear();
				offer.str(string());
				offer.clear();
				currentState = CHOOSING;
			}
		break;
		}
	}
}

void GameScreenLevel2::Choosing(float deltaTime, SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_RETURN:
			if (second == true)
			{
				result = (one * 10) + two;
			}
			else
			{
				result = one;
			}
			first = false;
			second = false;

			if (result > 22)
			{
				boxchoice.str(string());
				boxchoice.clear();
				boxchoice << "You can't have that box!" << endl;
				boxresult.str(string());
				boxresult.clear();
			}
			else
			{
				if (a[result - 1] == NULL || a[result - 1] == playerBox)
				{
					boxchoice.str(string());
					boxchoice.clear();
					boxchoice << "You can't have that box!" << endl;
					boxresult.str(string());
					boxresult.clear();
				}
				else
				{
					if (!firstbox)
					{
						std::ostringstream ss;
						ss << a[result - 1];
						std::string s(ss.str());

						//std::to_string(a[result]);
						bourbon = ss.str();

						if (r)
						{
							fourth = a[result - 1];
							q = false;
							w = false;
							t = false;
							r = false;
						}
						if (t)
						{
							third = a[result - 1];
							r = true;
							w = false;
						}
						if (w)
						{
							secondd = a[result - 1];
							t = true;
							q = false;
						}
						if (q)
						{
							firstt = a[result - 1];
							w = true;
						}

						//cout << "Update: " << bourbon << endl;
						theBoxes[result - 1]->dead = true;

						boxchoice.str(string());
						boxchoice.clear();
						boxchoice << "You've chosen " << result << endl;

						boxresult.str(string());
						boxresult.clear();
						boxresult << "That box had $" << a[result - 1] << endl;

						if (result < 23)
						{
							a[result - 1] = NULL;
						}

						round++;


						if (round == 4 || round == 8 || round == 12 || round == 16)
						{
							cout << firstt << " " << secondd << " " << third << " " << fourth << endl;
							currentState = THINKING;
							thinkingTime = false;
						}
						if (round == 20)
						{
							finalTime = true;
							currentState = FINAL;
						}
					}
					if (firstbox)
					{
						boxchoice << "You've chosen " << result << endl;
						playerBox = a[result - 1];
						theBoxes[result - 1]->moveBox = true;
						player = true;
						firstbox = false;
					}
				}
			}
			break;
		}
	}
}

void GameScreenLevel2::Final(float deltaTime, SDL_Event e)
{
	if (finalTime)
	{
		int intA[22];

		for (int m = 0; m < 22; m++)
		{
			intA[m] = a[m];
		}

		//Now we call the sort function
		sort(intA, intA + 22);

		for (int i = 1; i< theBoxes.size(); i++)
		{
			smallest = intA[20];
			biggest = intA[21];
			cout << intA[i] << " ";
		}

		finaloffer = (biggest - smallest) / 2 + smallest;

		offer.str(string());
		offer.clear();
		offer << "I offer you $" << finaloffer << endl;

		finalTime = false;

		NoFinal = true;

		currentState = DOND;
	}
	
}