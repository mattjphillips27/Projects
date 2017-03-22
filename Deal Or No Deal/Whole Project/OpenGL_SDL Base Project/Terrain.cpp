#include "Terrain.h"
//#include <GL\gl.h>
//#include <GL\glu.h>
//#include "../gl/glut.h"
#include <cstdio>

//-----------------------------------------------------------------------------------------------

Terrain::Terrain()
{
}

//-----------------------------------------------------------------------------------------------

Terrain::~Terrain()
{
}

//-----------------------------------------------------------------------------------------------

bool Terrain::Initialise()
{
	const char heightmapFilename[] = "heightmap.raw";
	FILE *pFile;
	fopen_s(&pFile, heightmapFilename, "rb");
	if (!pFile)
		return false;

	fread(&heightmap, TERRAIN_SIZE * TERRAIN_SIZE, 1, pFile);
	fclose(pFile);

	return true;
}

//-----------------------------------------------------------------------------------------------

void Terrain::Render()
{
	//glPolygonMode(GL_FRONT, GL_LINE);

	//Draw the terrain
	for (int z = 0; z < TERRAIN_SIZE - 1; ++z)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < TERRAIN_SIZE; ++x)
		{
			//Render two vertices of the strip at once
			float scaledHeight = heightmap[z * TERRAIN_SIZE + x] / SCALE_FACTOR;
			float nextScaledHeight = heightmap[(z + 1)* TERRAIN_SIZE + x] / SCALE_FACTOR;

			glTexCoord2f((GLfloat)x/TERRAIN_SIZE*8, (GLfloat)z/TERRAIN_SIZE*8);
			glVertex3f(static_cast<GLfloat>(x - TERRAIN_SIZE/2), scaledHeight, static_cast<GLfloat>(z - TERRAIN_SIZE/2));

			glTexCoord2f((GLfloat)x/TERRAIN_SIZE*8, (GLfloat)(z+1)/TERRAIN_SIZE*8);
			glVertex3f(static_cast<GLfloat>(x - TERRAIN_SIZE/2), nextScaledHeight, static_cast<GLfloat>(z + 1 - TERRAIN_SIZE/2));
		}
		glEnd();
	}

	//draw the water
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-TERRAIN_SIZE/2.1f, WATER_HEIGHT, TERRAIN_SIZE/2.1f);

		glTexCoord2f(TERRAIN_SIZE/4.0f, 0.0);
		glVertex3f(TERRAIN_SIZE/2.1f, WATER_HEIGHT, TERRAIN_SIZE/2.1f);

		glTexCoord2f(TERRAIN_SIZE/4.0f, TERRAIN_SIZE/4.0f);
		glVertex3f(TERRAIN_SIZE/2.1f, WATER_HEIGHT, -TERRAIN_SIZE/2.1f);

		glTexCoord2f(0.0, TERRAIN_SIZE/4.0f);
		glVertex3f(-TERRAIN_SIZE/2.1f, WATER_HEIGHT, -TERRAIN_SIZE/2.1f);
	glEnd();
}

//-----------------------------------------------------------------------------------------------

void Terrain::Update(float deltaTime)
{
}

//-----------------------------------------------------------------------------------------------