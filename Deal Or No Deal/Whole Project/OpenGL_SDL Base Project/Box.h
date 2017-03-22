#ifndef _BOX_H
#define _BOX_H

#include "Commons.h"
#include "Texture2D.h"
#include "object3DS.h"
#include "Texture2D.h"
#include "Audio.h"
//#include "GameScreenLevel2.h"
#include <vector>

#pragma once
class Box
{
public:
	Box(float);

	~Box();

	void Render();

	void Update(float deltaTime, SDL_Event e);

	float rotate;
	bool dead;
	float money;

	bool moveBox;
	float movePos;

	Texture2D* tbox = new Texture2D();
	Object3DS*	mBox;

	//float money();
};

#endif

