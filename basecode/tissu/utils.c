#include "utils.h"
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

	glColor3f(p_color.x,p_color.y,p_color.z);

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
					glNormal3f(cosf(alpha)*cosf(beta),sinf(beta), sinf(alpha)*cosf(beta));
					glVertex3f(cosf(alpha)*cosf(beta),sinf(beta), sinf(alpha)*cosf(beta));
					glNormal3f(cosf(alpha)*cosf(beta+step),sinf(beta+step), sinf(alpha)*cosf(beta+step));
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
void drawLines(vec3 p_pos1, vec3 p_pos2, vec3 p_color)
{
	glColor3f(p_color.x,p_color.y,p_color.z);

	glBegin(GL_LINES);
		glVertex3f(p_pos1.x,p_pos1.y,p_pos1.z);
		glVertex3f(p_pos2.x,p_pos2.y,p_pos2.z);
	glEnd();
}


/*!
 *	\brief	to load a texture from a BMP file
 *
 *	\param	p_path	the path to load the BMP picture
 *
 *	\return	a GLuint = the ID of the OpenGL texture if loaded successfully, 0 else
 */
GLuint loadTexture(char * p_path)
{
	GLuint id = 0;

	SDL_Surface * pic = SDL_LoadBMP(p_path);

	if(!pic)
		return id;

	glGenTextures(1,&id);

	glBindTexture(GL_TEXTURE_2D,id);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,pic->w,pic->h,0,GL_BGR_EXT,GL_UNSIGNED_BYTE,pic->pixels);

	return id;
}