#include "object3DS.h"
#include "../gl/glut.h"
#include "3dsLoader.h"
#include <iostream>
#include <fstream>
using namespace::std;
//--------------------------------------------------------------------------------------------------
Object3DS::Object3DS(Vector3D	startPosition, string	modelFileName){
	//start	position.
	mPosition = startPosition;
	//3ds	file	to	load.
	std::strcpy(fileName, modelFileName.c_str());
	loadModel();
}
//--------------------------------------------------------------------------------------------------
void Object3DS::loadModel()
{
	if (fileName[0] != '-')
		Load3DS(&object, fileName);
}
//--------------------------------------------------------------------------------------------------
void Object3DS::loadTexture()
{
	//TODO: Load	a	texture	to	map	to	the	object.
}
//--------------------------------------------------------------------------------------------------
void Object3DS::update(float deltaTime)
{
	//TODO:	Move	object	here.
}
//--------------------------------------------------------------------------------------------------
void Object3DS::render()
{
	

	glPushMatrix();
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	//glBindTexture(GL_TEXTURE_2D,	object.id_texture);	//	We	set	the	active	texture	
	glBegin(GL_TRIANGLES);	//	glBegin	and	glEnd	delimit	the	vertices	that	define	a	primitive	(in	our	case	triangles)
	for (int l_index = 0; l_index<object.polygons_qty; l_index++)
	{
		//----------------- FIRST	VERTEX	----------------//
		//	Texture	coordinates	of	the	first	vertex
		glTexCoord2f(	object.mapcoord[	object.polygon[l_index].a	].u,
		 		object.mapcoord[	object.polygon[l_index].a	].v);

		//	Coordinates	of	the	first	vertex
		glVertex3f(object.vertex[object.polygon[l_index].a].x,
			object.vertex[object.polygon[l_index].a].y,
			object.vertex[object.polygon[l_index].a].z);	//Vertex	definition
		//----------------- SECOND	VERTEX	-----------------
		//	Texture	coordinates	of	the	second	vertex
		glTexCoord2f(	object.mapcoord[	object.polygon[l_index].b	].u,
		 		object.mapcoord[	object.polygon[l_index].b	].v);

		//	Coordinates	of	the	second	vertex
		glVertex3f(object.vertex[object.polygon[l_index].b].x,
			object.vertex[object.polygon[l_index].b].y,
			object.vertex[object.polygon[l_index].b].z);

		//----------------- THIRD	VERTEX	-----------------
		//	Texture	coordinates	of	the	third	vertex
		glTexCoord2f(	object.mapcoord[	object.polygon[l_index].c	].u,
		 		object.mapcoord[	object.polygon[l_index].c	].v);

		//	Coordinates	of	the	Third	vertex
		glVertex3f(object.vertex[object.polygon[l_index].c].x,
			object.vertex[object.polygon[l_index].c].y,
			object.vertex[object.polygon[l_index].c].z);
	}
	glEnd();
	glPopMatrix();
}
//--------------------------------------------------------------------------------------------------