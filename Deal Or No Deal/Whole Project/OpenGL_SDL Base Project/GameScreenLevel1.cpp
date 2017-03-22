#include "GameScreenLevel1.h"
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
#include "GameOver.h"

using namespace::std;

vector<Teapot*> theTeapots;
class GameOver;




//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1(GameScreenManager* gsm) : GameScreen()
{
	gsmm = gsm;


	movementY = 8.0f;
	movementX = 0.0f;

	position.x = 0.0;
	position.y = 30.0;
	position.z = 3.0;
	
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

	health = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	court->Load("court.raw", 512, 512);
	denzil->Load("patrick.raw", 512, 512);

	m_Denzil = new Object3DS(Vector3D(0.0f, 0.0f, 0.0f), "patrick.3ds");


	for (int i = 0; i < 20; i++) 
	{
		theTeapots.push_back(new Teapot(this));
	}
}

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::~GameScreenLevel1()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	delete this;
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::DrawCourt()
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

void GameScreenLevel1::setLight() {
	float light_pos[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}



void GameScreenLevel1::OutputLine(float x, float y, string text)
{
	glRasterPos2f(x, y);  // where to start drawing
	for (int i = 0; i < text.size(); i++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}

void GameScreenLevel1::Render()
{
	glColor3f(1.0, 1.0, 1.0);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GameScreen::Render();

	

	glEnable(GL_TEXTURE_2D);
	glTranslatef(0.0, 0.0f, -40.0f);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(-45, 0.0, 1.0, 0.0);

		glPushMatrix();
			glTranslatef(-6.0, 5.0f, -20.0f);
			glRotatef(90, 1.0, 0.0, 0.0);
			for (int i = 0; i < theTeapots.size(); i++)
			{
				theTeapots[i]->Render();
			}
		glPopMatrix();

		
		glPushMatrix();
			glRotatef(90, 1.0, 0.0, 0.0);
			glRotatef(-90, 0.0, 1.0, 0.0);
			glTranslatef(movementX, movementY, 1.0);
			playerboundingSphere = new Sphere(position, 0.6);
			glutWireSphere(playerboundingSphere->GetBoundingRadius(), 10, 10);
			glScalef(3, 3, 3);
			glBindTexture(GL_TEXTURE_2D, denzil->GetID());
			m_Denzil->render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.0f, -15.0f);
		setLight();
		DrawCourt();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.0f, 5.0f);
		glRotatef(180, 1.0, 0.0, 0.0);
		setLight();
		DrawCourt();
		glPopMatrix();

		// first render the teapot, then
		
		glColor3f(8.0, 0.0, 8.0);
		
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
				glLoadIdentity();
				gluOrtho2D(0, 100, 0, 100);
				OutputLine(5, 95, ss.str());
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

	

	glDisable(GL_TEXTURE_2D);
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	ss.str(string());
	ss.clear();
	ss << "Health:  " << health << " " << "Time: " << mCurrentTime << endl;
	
	GameScreen::Update(deltaTime, e);

	mCurrentTime += deltaTime;

	playerboundingSphere->Update(position);

	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			movementX += 0.5;
			position.z += 0.5;
			break;

		case SDLK_d:
			movementX -= 0.5;
			position.z -= 0.5;
			break;

		case SDLK_s:
			movementY += 0.5;
			position.y += 0.5;
			break;

		case SDLK_w:
			movementY -= 0.5;
			position.y -= 0.5;
			break;
		}
	}
	
	// Call Teapot update
	for (int i = 0; i < theTeapots.size(); i++) 
	{
		theTeapots[i]->Update(deltaTime);
	}

	// check for collisions
	for (int i = 0; i < theTeapots.size(); i++) 
	{
		Collision::SphereSphereCollision(playerboundingSphere, theTeapots[i]->GetBoundingSphere());
	}


	if (movementY < -18)
	{
		gsmm->ChangeScreen(SCREEN_MENU);
	}

	if (health <= 0)
	{
		gsmm->SetTime(mCurrentTime);
		gsmm->ChangeScreen(SCREEN_GAMEOVER);
	}
	
}

//--------------------------------------------------------------------------------------------------