#ifndef _TEAPOT_H 
#define _TEAPOT_H

#pragma once
#include "Commons.h"
#include "Texture2D.h"
#include "object3DS.h"
#include "Audio.h"
#include "GameScreenLevel1.h"
#include <vector>

class Sphere;
class GameScreenLevel1;

class Teapot
{
public:
	Teapot(GameScreenLevel1* gsl1);
	~Teapot() { }
	void Update(float deltaTime);
	void Render();
	Sphere * GetBoundingSphere();
	Sphere * boundingSphere;

private:
	Vector3D position;
	float scale;
	Vector3D velocity;
	Vector3D acceleration;

	bool doonce;

	Object3DS*	m_earth;

	float rands;

	int i = 0;

	GameScreenLevel1* pllop;
};
#endif

