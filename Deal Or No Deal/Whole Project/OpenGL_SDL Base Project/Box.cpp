#include "Box.h"
#include "object3DS.h"
#include "Texture2D.h"
#include <iostream>
#include <algorithm>

using namespace::std;


Box::Box(float m)
{
	tbox->Load("bo1x.bmp", 1024, 1024);

	mBox = new Object3DS(Vector3D(0.0f, 0.0f, 0.0f), "box1.3ds");

	

	money = m;
	rotate = 0.0;
	//cout << money << endl;
	dead = false;
	moveBox = false;
	movePos = 300000000.0;
}

Box::~Box()
{

}

void Box::Render()
{
	
	glPushMatrix();

	if (dead)
	{
		glRotatef(rotate, 1.0, 0.0, 0.0);
	}
	if (moveBox)
	{
		//glColor3f(8.0, 0.0, 8.0);
		glTranslatef(movePos, 20.0, 0.0);
	}
		mBox->render();
	glPopMatrix();
}

void Box::Update(float deltaTime, SDL_Event e)
{
	if (dead)
	{
		if (rotate < 90)
			rotate += 0.2;
	}
	
	
}

