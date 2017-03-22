#include <stdio.h>
#include <stdlib.h>
#include "Commons.h"
#include "3dsLoader.h"
#include <sys\stat.h>
//--------------------------------------------------------------------------------------------------
long filelength(int f)
{
	struct stat	buf;
	fstat(f, &buf);
	return(buf.st_size);
}
//--------------------------------------------------------------------------------------------------
char Load3DS(obj_type_ptr	p_object, char *p_filename)
{
	int i; //Index	variable
	FILE	*inFile; //File	pointer
	unsigned short chunkId, s_temp; //Chunk	identifier
	unsigned int chunkLength; //Chunk	lenght
	unsigned char name; //Char	variable
	unsigned short size; //Number	of	elements	in	each	chunk
	unsigned short faceFlag; //Flag	that	stores	some	face	information
	if ((inFile = fopen(p_filename, "rb")) == NULL)	return 0; //Open	the	file

	while (ftell(inFile)	<	filelength(fileno(inFile))) //Loop	to	scan	the	whole	file
	{
		fread(&chunkId, 2, 1, inFile); //Read	the	chunk	header
		fread(&chunkLength, 4, 1, inFile); //Read	the	length	of	the	chunk
		//getchar();	//Insert	this	command	for	debug	(to	wait	for	keypress	for	each	chuck reading)
		switch (chunkId)
		{
			//----------------- MAIN3DS	-----------------
			//	Description:	Main	chunk,	contains	all	the	other	chunks
			//	Chunk	ID:	4d4d	
			//	Chunk	Lenght:	0	+	sub	chunks
			//-------------------------------------------
		case 0x4d4d:
			break;
			//----------------- EDIT3DS	-----------------
			//	Description:	3D	Editor	chunk,	objects	layout	info	
			//	Chunk	ID:	3d3d	(hex)
			//	Chunk	Lenght:	0	+	sub	chunks
			//-------------------------------------------
		case 0x3d3d:
			break;
			//--------------- EDIT_OBJECT	---------------
			//	Description:	Object	block,	info	for	each	object
			//	Chunk	ID:	4000	(hex)
			//	Chunk	Lenght:	len(object	name)	+	sub	chunks//-------------------------------------------
		case 0x4000:
			i = 0;
			do
			{
				fread(&name, 1, 1, inFile);
				p_object->name[i] = name;
				i++;
			} while (name != '\0' &&	i<20);
			break;
			//--------------- OBJ_TRIMESH	---------------
			//	Description:	Triangular	mesh,	contains	chunks	for	3d	mesh	info
			//	Chunk	ID:	4100	(hex)
			//	Chunk	Lenght:	0	+	sub	chunks
			//-------------------------------------------
		case 0x4100:
			break;
			//--------------- TRI_VERTEXL	---------------
			//	Description:	Vertices	list
			//	Chunk	ID:	4110	(hex)
			//	Chunk	Lenght:	1	x	unsigned	short	(number	of	vertices)	
			//													+	3	x	float	(vertex	coordinates)	x	(number	of	vertices)
			//													+	sub	chunks
			//-------------------------------------------
		case 0x4110:
			fread(&size, sizeof(unsigned short), 1, inFile);
			p_object->vertices_qty = size;
			for (i = 0; i<size; i++)
			{
				fread(&p_object->vertex[i].x, sizeof(float), 1, inFile);
				fread(&p_object->vertex[i].y, sizeof(float), 1, inFile);
				fread(&p_object->vertex[i].z, sizeof(float), 1, inFile);
			}
			break;
			//--------------- TRI_FACEL1	----------------//	Description:	Polygons	(faces)	list
			//	Chunk	ID:	4120	(hex)
			//	Chunk	Lenght:	1	x	unsigned	short	(number	of	polygons)	
			//													+	3	x	unsigned	short	(polygon	points)	x	(number	of	polygons)
			//													+	sub	chunks
			//-------------------------------------------
		case 0x4120:
			fread(&size, sizeof(unsigned short), 1, inFile);
			p_object->polygons_qty = size;
			for (i = 0; i<size; i++)
			{
				fread(&s_temp, sizeof(unsigned short), 1, inFile);
				p_object->polygon[i].a = s_temp;
				fread(&s_temp, sizeof(unsigned short), 1, inFile);
				p_object->polygon[i].b = s_temp;
				fread(&s_temp, sizeof(unsigned short), 1, inFile);
				p_object->polygon[i].c = s_temp;
				fread(&faceFlag, sizeof(unsigned short), 1, inFile);
			}
			break;
			//------------- TRI_MAPPINGCOORS	------------
			//	Description:	Vertices	list
			//	Chunk	ID:	4140	(hex)
			//	Chunk	Lenght:	1	x	unsigned	short	(number	of	mapping	points)	
			//													+	2	x	float	(mapping	coordinates)	x	(number	of	mapping	points)
			//													+	sub	chunks
			//-------------------------------------------
		case 0x4140:
			fread(&size, sizeof(unsigned short), 1, inFile);
			for (i = 0; i<size; i++)
			{
				fread(&p_object->mapcoord[i].u, sizeof(float), 1, inFile);
				fread(&p_object->mapcoord[i].v, sizeof(float), 1, inFile);
			}
			break;
			//----------- Skip	unknow	chunks	------------
			//We	need	to	skip	all	the	chunks	that	currently	we	don't	use
			//We	use	the	chunk	lenght information	to	set	the	file	pointer
			//to	the	same	level	next	chunk
			//-------------------------------------------
		default:
			fseek(inFile, chunkLength - 6, SEEK_CUR);
		}
	}
	fclose(inFile); //Close	the	file.
	return (1);
}
//--------------------------------------------------------------------------------------------------