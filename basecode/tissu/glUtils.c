#include "glUtils.H"
#include <math.h>



/*!
 * \ to draw a referential at the current referential position & orientation
 */
void drawRef()
{
	glBegin(GL_LINES);

		// X axis
		glColor3f(  1.0f , 0.0f , 0.0f );
		glVertex3f( 0.0f , 0.0f , 0.0f );
		glVertex3f( 1.0f , 0.0f , 0.0f );
		// Y axis
		glColor3f(  0.0f , 1.0f , 0.0f );
		glVertex3f( 0.0f , 0.0f , 0.0f );
		glVertex3f( 0.0f , 1.0f , 0.0f );
		// Z axis
		glColor3f(  0.0f , 0.0f , 1.0f );
		glVertex3f( 0.0f , 0.0f , 0.0f );
		glVertex3f( 0.0f , 0.0f , 1.0f );

	glEnd();	
}

/*!
 *	\brief	to draw a sphere at the given position with the given diameter & the given color
 *
 *	\param	p_pos	position of the center of the sphere
 *	\param	p_size	the diameter of the sphere	
 *	\param	p_color	the color of the sphere
 */
void drawSphere(vec3 p_pos, float p_size, vec3 p_color)
{
	int i,j;
	float step;
	float alpha, beta;

	glPushMatrix();

		glTranslatef(p_pos.x,p_pos.y,p_pos.z);
		glScalef(p_size/2.0f,p_size/2.0f,p_size/2.0f);

		step = (float)(M_PI / (float)SECTIONS);
		beta = (float)(-M_PI/2.0f);
	
		// Draw the sphere (radius = 1)
		for(i=0; i < SECTIONS ; i++)
		{
			alpha = 0.0f;
			glBegin(GL_QUAD_STRIP);
				for(j=0; j <= 2*SECTIONS ; j++)
				{
					glVertex3f(cosf(alpha)*cosf(beta),sinf(beta), sinf(alpha)*cosf(beta));
					glVertex3f(cosf(alpha)*cosf(beta+step),sinf(beta+step), sinf(alpha)*cosf(beta+step));
					alpha += step;
				}
			glEnd();
			beta += step;
		}

	glPopMatrix();
}

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

