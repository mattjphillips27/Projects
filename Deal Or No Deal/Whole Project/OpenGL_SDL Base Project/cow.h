#ifndef _COW_H 
#define _COW_H
#pragma once
#include "Commons.h"
#include "Texture2D.h"
#include "object3DS.h"
#include "Audio.h"
#include <vector>

class Sphere;

class cow
{
public:
	cow();

	~cow(); 

	void Update(float deltaTime);
	void Render();

	Sphere * GetBoundingSphere();
	

private:

	Vector3D position;
	float scale;
	Vector3D velocity;
	Vector3D acceleration;

	Texture2D* t_Cow = new Texture2D();
	Sphere * boundingSphere;

	Object3DS*	m_Cow;
	float rands;

	float cowposition = 0.0f;

	int p;


};
#endif

