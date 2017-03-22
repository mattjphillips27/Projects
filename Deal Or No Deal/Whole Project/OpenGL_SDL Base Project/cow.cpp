
#include "cow.h"
#include "Collision.h"
#include <math.h>
#include <stdlib.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Commons.h"
#include <iostream>
#include <vector>
#include "Audio.h"
#include "object3DS.h"

using namespace::std;

cow::cow()
{



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

	m_Cow = new Object3DS(Vector3D(0.0f, 0.0f, 0.0f), "cow.3ds");

	boundingSphere = new Sphere({ position.z, position.y, position.x }, 1.4);
}

void cow::Render()
{
	
	
	if (boundingSphere->GetCollided())
	{
		//Audio::Audio("Music/meh.mp3");
		glColor3f(1.0, 0.0, 0.0);
	
	}
	else
	{

	}
	

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	//glutWireTeapot(1);
	glScalef(0.03, 0.03, 0.03);
	m_Cow->render();
	glutWireSphere(boundingSphere->GetBoundingRadius(), 10, 10);
	glPopMatrix();

}



void cow::Update(float deltaTime)
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
	}

	boundingSphere->Update(position);
}

Sphere * cow::GetBoundingSphere()
{
	return boundingSphere;
}