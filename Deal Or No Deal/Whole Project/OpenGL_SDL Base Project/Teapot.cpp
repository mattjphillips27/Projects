
#include "Teapot.h"
#include "Collision.h"
#include <math.h>
#include <stdlib.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Commons.h"
#include <iostream>
#include <vector>
#include "Audio.h"

using namespace::std;

Teapot::Teapot(GameScreenLevel1* gsl1)
{

	pllop = gsl1;

	// use random numbers to initialise the position, scale and velocity
	position.x = 0.0f * (float)rand() / (RAND_MAX)-5;
	position.y = 40.0f * (float)rand() / (RAND_MAX)-5;
	position.z = 20.0f * (float)rand() / (RAND_MAX)-5;

	//position.x = 0.0f;
	//position.y = 0.0f;
	//position.z = 20.0f * (float)rand() / (RAND_MAX)-5;;

	//scale = (float)rand() / ((RAND_MAX / 2));

	velocity.x = 50.0f * (float)rand() / ((RAND_MAX)* 1000) - 0.005;
	velocity.y = 50.0f * (float)rand() / ((RAND_MAX)* 1000) - 0.005;
	velocity.z = 50.0f * (float)rand() / ((RAND_MAX)* 1000) - 0.005;

	rands = (20.0f * (float)rand() / (RAND_MAX)) + 5;

	acceleration = { rands, 0.0f, 0.0f };

	boundingSphere = new Sphere(position, 1.4);
}

void Teapot::Render()
{
	if (boundingSphere->GetCollided())
	{
		if (doonce)
		{
			Audio::Audio("Music/meh.mp3");
			glColor3f(1.0, 0.0, 0.0);
			pllop->health--;
			doonce = false;
		}

	}
	else
	{
		doonce = true;
	}


	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glutWireTeapot(1);
	glutWireSphere(boundingSphere->GetBoundingRadius(), 10, 10);
	glPopMatrix();

}



void Teapot::Update(float deltaTime)
{
	boundingSphere->SetCollided(false);

	position.x += (velocity.x * deltaTime + acceleration.x * (0.5 * deltaTime * deltaTime));
	position.y += (velocity.y * deltaTime + acceleration.y * (0.5 * deltaTime * deltaTime));
	position.z += (velocity.z * deltaTime + acceleration.z * (0.5 * deltaTime * deltaTime));

	velocity.x += acceleration.x * deltaTime;
	velocity.z += acceleration.y * deltaTime;
	velocity.y += acceleration.z * deltaTime;


	if (position.x > 5 || position.x < -5)
	{
		velocity.x *= -1;
		Audio::Audio("Music/BallPop2.mp3");
	}

	boundingSphere->Update(position);
}

Sphere * Teapot::GetBoundingSphere()
{
	return boundingSphere;
}