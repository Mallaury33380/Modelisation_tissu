#ifndef _GLUTILS_
#define _GLUTILS_

#define SECTIONS	12

#include "./SDL2-2.0.10/include/SDL.h"
#include <Windows.h>
#include <gl/GL.h>
#include "./vec3/include/vec3.h"

#include <time.h>


/*! To define the TRUE value for boolean */
#define TRUE	1
/*! To define the FALSE value for boolean */
#define FALSE	0

/*! defintion of the boolean type : to be used with the macros TRUE & FALSE*/
typedef unsigned char bool;

/*! to create a random number between 0 and 1 */
#define RANDOM_0_1	(rand()/(float)(RAND_MAX+1))


/*!
 * \ to draw a referential at the current referential position & orientation
 */
void drawRef();

/*!
 *	\brief	to draw a sphere at the given position with the given diameter & the given color
 *
 *	\param	p_pos	position of the center of the sphere
 *	\param	p_size	the diameter of the sphere	
 *	\param	p_color	the color of the sphere
 */
void drawSphere(vec3 p_pos, float p_size, vec3 p_color);

/*!
 *	\brief to draw a line between 2 positions
 *
 *	\param	p_pos1	first position to draw the line
 *	\param	p_pos2	second position to draw the line
 *	\param	p_color	the color to draw the line
 */
void drawLines(vec3 p_pos1, vec3 p_pos2, vec3 p_color);

/*!
 *	\brief	to load a texture from a BMP file
 *
 *	\param	p_path	the path to load the BMP picture
 *
 *	\return	a GLuint = the ID of the OpenGL texture if loaded successfully, 0 else
 */
GLuint loadTexture(char * p_path);

#endif