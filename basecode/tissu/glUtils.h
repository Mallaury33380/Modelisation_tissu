#ifndef _GLUTILS_
#define _GLUTILS_

#define SECTIONS	12

#include "./SDL2-2.0.3/include/SDL.h"
#include <Windows.h>
#include <gl/GL.h>
#include "vec3/include/vec3.H"
#include "tissu.H"


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
 *	\brief	to draw the fabric using GL primitives (GL_TRIANGLES / GL_LINE_LOOP)
 *
 *	\param	p_positions	an array of vec3 to define the position of each particle of the fabric
 *	\param	p_width		number of particles on the width axis
 *	\param	p_length	number of particles on the length axis
 *	\param	p_primitive	primitive to use to draw (GL_TRIANGLES / GL_LINE_LOOP)
 */
void drawFabric(particle ** p_positions, int p_width, int p_length, unsigned int p_primitive);



#endif