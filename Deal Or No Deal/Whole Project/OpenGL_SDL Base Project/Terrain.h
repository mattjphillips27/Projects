#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "../gl/glut.h"
#include "Constants.h"

class Terrain
{
//--------------------------------------------------------------------------------------------------
public:
	Terrain();
	~Terrain();

	bool		Initialise();
	void		Render();
	void		Update(float deltaTime);

//--------------------------------------------------------------------------------------------------
private:
	GLubyte heightmap[TERRAIN_SIZE * TERRAIN_SIZE];
};

#endif //_TERRAIN_H