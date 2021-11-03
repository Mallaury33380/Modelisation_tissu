#include "tissu.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>



/*! normals to draw the fabric */
vec3 * g_normals = NULL;
/*! positions to draw the fabric */
vec3 * g_positions = NULL;
/*! texture coordinates to draw the fabric with a texture applied on it */
vec3 * g_texcoords = NULL;
/*! list of indices to specify the faces of the fabric */
unsigned int * g_faces = NULL;
/*! Texture ID */
GLuint g_texID = 0;

/*! Parametrage*/
extern parametrage Parametrage;


/*!<	
 *	\brief	function to initialize all the particles properties (but the springs)
 *
 *	\param	p_array		the array of particles
 *	\param	p_width		the width in meter
 *	\param	p_length	the length in meter
 *	\param	p_nbPartW	number of particles on width axis
 *	\param	p_nbPartL	number of particles on length axis
 *	\param	p_obstacles	the array of obstacles
 *	\param	p_nbObstacles	the number of obstacles
 */

void initializeArrayOfParticles(particle ** p_array, float p_width, float p_length, int p_nbPartW, int p_nbPartL, obstacle * p_obstacles, int p_nbObstacles)
{
	//Random
	srand(time(NULL));

	
	// Create particles
	// TODO

	vec3 pos;
	vec3 speed;
	
	float lW = p_width / p_nbPartW;
	float ll = p_length / p_nbPartL;

	speed = set3(0, 0, 0);

	for(int i=0;i< p_nbPartW;i++)
	{
		for (int j = 0; j < p_nbPartL; j++)
		{
			//Calcul particle's position
			//Drapeau	
			if (Parametrage.Flag && !(Parametrage.Medusa[0])) pos = set3(i * lW, (j * ll)+SPACE,0);
			//Fabric
			else pos = set3(i * lW, 1, j * ll);

			p_array[i][j]=createParticle(j * p_nbPartW + i, DEFAULT_MASS, DEFAULT_SIZE, TRUE, pos, speed, FRICTION);
			//Determination of l0
			p_array[i][j].l0[0] = p_width / p_nbPartW;
			p_array[i][j].l0[1] = p_length / p_nbPartL;
			p_array[i][j].l0[2] = sqrtf(p_array[i][j].l0[0] * p_array[i][j].l0[0] + p_array[i][j].l0[1] * p_array[i][j].l0[1]);

		}
	}
	


	// Create links between particles
	// TODO

	for (int l = 0; l < p_nbPartW; l++)
	{
		for(int m = 0;m < p_nbPartL; m++)
		{
			// Compression neighbours
			if (l != 0)
			{
				p_array[l][m].m_compression[0] = &p_array[l - 1][m];
			}
			if (l != (p_nbPartW-1))
			{
				p_array[l][m].m_compression[1] = &p_array[l + 1][m];
			}
			if (m != 0)
			{
				p_array[l][m].m_compression[2] = &p_array[l][m-1];
			}
			if (m != (p_nbPartL-1))
			{
				p_array[l][m].m_compression[3] = &p_array[l][m+1];
			}

			// Shear neighbours
			if (l != 0 && m != 0)
			{
				p_array[l][m].m_shear[0] = &p_array[l - 1][m - 1];
			}
			if (l != 0 && m!= (p_nbPartL-1))
			{
				p_array[l][m].m_shear[1] = &p_array[l - 1][m + 1];
			}
			if (l!= (p_nbPartW-1) && m!= (p_nbPartL-1))
			{
				p_array[l][m].m_shear[2] = &p_array[l + 1][m + 1];
			}
			if (l!= (p_nbPartW-1) && m!=0)
			{
				p_array[l][m].m_shear[3] = &p_array[l + 1][m - 1];
			}


			// Flexion neighbours
			if (l >1)
			{
				p_array[l][m].m_flexion[0] = &p_array[l - 2][m];
			}
			if (l < p_nbPartW-2)
			{
				p_array[l][m].m_flexion[1] = &p_array[l + 2][m];
			}
			if (m > 1)
			{
				p_array[l][m].m_flexion[2] = &p_array[l][m - 2];
			}
			if (m < p_nbPartL-2)
			{
				p_array[l][m].m_flexion[3] = &p_array[l][m + 2];
			}
		}
	}


	
	// Initialize obstacles 
	// TODO
	for (int k = 0; k < p_nbObstacles; k++)
	{
		p_obstacles[k].m_friction = (float)(rand() % 100) / 100;
		p_obstacles[k].m_size = DEFAULT_SIZE * SIZE_OBSTACLE;

		//Move all obstacles if we want a flag
		if (Parametrage.Flag || Parametrage.Medusa[0])
		{
			p_obstacles[k].m_size = p_obstacles[k].m_size / SIZE_OBSTACLE;
			p_obstacles[k].m_position = set3(CLEAR_OBSTACLE, CLEAR_OBSTACLE, CLEAR_OBSTACLE);
		}
		//Initialize the obstacle's position
		else p_obstacles[k].m_position = set3((float)(rand() % 100) / 100 , (float)(rand() % 50) / 100, (float)(rand() % 100) / 100);
	}
}

/*!<	
 *	\brief	function to generate all the particles to be used to do the simulation 
 *
 *	\param	p_width		the width in meter
 *	\param	p_length	the length in meter
 *	\param	p_nbPartW	number of particles on width axis
 *	\param	p_nbPartL	number of particles on length axis
 *	\param	p_obstacles	the array of obstacles
 *	\param	p_nbObstacles	the number of obstacles
 *
 *	\return	an array of particles initialised so the size of the fabric is the one wished, NULL if an error occurred
 */
particle ** createFabric(float p_width, float p_length, int p_nbPartW, int p_nbPartL, obstacle * p_obstacles, int p_nbObstacles)
{
	int i,j;
	particle ** array = NULL;

	if( p_width<=0.0f || p_length<=0.0f || p_nbPartW<=1 || p_nbPartL<=1 )
		return NULL;


	// Allocate the particles'array
	// TODO
	array = (particle **)calloc(p_nbPartW, sizeof(particle*));
	for (i = 0; i < p_nbPartL; i++ )
	{
		array[i] = (particle*)calloc(p_nbPartL, sizeof(particle));
	}

	// Initialize the particles'array
	initializeArrayOfParticles(array,p_width, p_length, p_nbPartW, p_nbPartL, p_obstacles, p_nbObstacles);

	return array;

}

/*!<	
 *	\brief	function to delete the fabric particles created before
 *
 *	\param	p_array		the particles
 *	\param	p_nbPartW	number of particles on width axis
 *	\param	p_nbPartL	number of particles on length axis
 */
void deleteFabric(particle ** p_array, int p_nbPartW, int p_nbPartL)
{
	int i;

	if(!p_array)
		return;
	
	// Delete particles'array
	// TODO
	if (p_array) {
		for (i = 0; i < p_nbPartL; i++) {
			if (p_array[i])
				free(p_array[i]);
		}
		free(p_array);
	}


	if(g_faces)
		free(g_faces);

	if(g_positions)
		free(g_positions);


	if(g_normals)
		free(g_normals);

	if(g_texcoords)
		free(g_texcoords);
}


/*!
 *	\brief to create a particle with the parameters given 
 *
 *	\param	p_num		the ID of the particle
 *	\param	p_mass		the mass of the particle
 *	\param	p_size		the size of the particle
 *	\param	p_static	does the particle can move or not ?
 *	\param	p_pos		the initial position of the particle
 *	\param	p_speed		the initial speed of the particle
 *	\param	p_friction	the friction coefficient to apply to the particle
 */
particle createParticle(int p_num, float p_mass, float p_size, bool p_static, vec3 p_pos, vec3 p_speed, float p_friction)
{
	int i;

	particle p;
	
	//Initialize particle's settings
	//TODO
	p.m_ID = p_num;
	p.m_mass = p_mass;
	p.m_size	= p_size;
	p.m_canMove = p_static;
	p.m_position[CURRENT]	= copy3(p_pos);
	p.m_position[NEXT]		= copy3(p_pos);	
	p.m_speed[CURRENT]		= copy3(p_speed);		
	p.m_speed[NEXT]			= copy3(p_speed);	
	p.m_friction = p_friction;

	// TODO	
	for (i = 0; i < 4; i++)
	{
		p.m_compression[i] = NULL;
		p.m_shear[i] = NULL;
		p.m_flexion[i] = NULL;
	}

	return p;
}

/*!<	
 *	\brief	function to update all the fabric particles 
 *
 *	\param	p_array		the particles
 *	\param	p_nbPartW	number of particles on width axis
 *	\param	p_nbPartL	number of particles on length axis
 *	\param	p_dt		the elapsed time to integrate the acceleration to calculate speed & position for each particle
 *	\param	p_obstacles	the obstacles to take into account in the simulation (array of obstacle structures)
 *	\param	p_nbObstacles	the number of obstacles stored in the array "p_obstacles"
 */
void updateFabric(particle ** p_array, int p_nbPartW, int p_nbPartL, float p_dt, obstacle * p_obstacles, int p_nbObstacles)
{
	static float lastingDt = 0.0f;
	int i,j;
	float y;

	if(!p_array)
		return;

	// count the lasting dt frame previous frame
	p_dt += lastingDt;

	// loop to integrate always using the integration step defined
	while(p_dt>INTEGRATION_STEP)
	{
		
		// update the particles position & speed
		// TODO.
		//Update in function of the mod
		for (i = Parametrage.Flag; i < p_nbPartW; i++)
		{
			for (j = 0; j < p_nbPartL; j++)
			{
				//Update Wind by Medusa
				if (Parametrage.Medusa[0])
				{
					y = Parametrage.Wind.y;
					//Propotional to the distance beetwen the center and the particul
					Parametrage.Wind.y += Parametrage.Medusa[1] *(1- ((sqrtf(pow(i-p_nbPartW/2,2)+pow(j-p_nbPartL/2,2)))/(sqrtf(pow(p_nbPartW/2, 2) + pow(p_nbPartL/2, 2)))));
				}

				updateParticle(&p_array[i][j],p_dt,p_obstacles,p_nbObstacles);
				finalizeParticle(&p_array[i][j]);
					
					//Establish the wind as before the update
				if (Parametrage.Medusa[0])
				{
					Parametrage.Wind.y = y;
				}
			}
		}
		//Power of medusa decrease with the time
		//Update Medusa[1]
		Parametrage.Medusa[1] = Parametrage.Medusa[1] * COEFF_MEDUSA;


		p_dt-=INTEGRATION_STEP;
	}
	// store the lasting dt for next frame
	lastingDt = p_dt;
}

/*!<	
 *	\brief	function to update a particle
 *
 *	\param	p_particle	the particle
 *	\param	p_dt		the elapsed time to integrate the acceleration to calculate speed & position for the particle
 *	\param	p_obstacles	the obstacles to take into account in the simulation (array of obstacle structures)
 *	\param	p_nbObstacles	the number of obstacles stored in the array "p_obstacles"
 */
void updateParticle(particle* p_particle, float p_dt, obstacle* p_obstacles, int p_nbObstacles)
{
	int i, k;
	vec3 op;
	float Decallage=0.01;

	//Gravity
	vec3 Gravity = set3(0,0,0);
	if (Parametrage.Gravity)
	{
		Gravity = set3(0, GRAVITY / p_particle->m_mass, 0);
	}

	//Friction
	vec3 Friction = div3(mul3(p_particle->m_speed[CURRENT], -FRICTION),p_particle->m_mass);

	//Reflect
	vec3 Reflect = set3(0, 0, 0);
	for (i = 0; i < p_nbObstacles; i++) {
		if (distance3(p_particle->m_position[CURRENT], p_obstacles[i].m_position) < p_obstacles[i].m_size / 2 + p_particle->m_size / 2 + Decallage) {
			Reflect = reflect3(p_particle->m_speed[CURRENT], sub3(p_obstacles[i].m_position, p_particle->m_position[CURRENT]));
			p_particle->m_position[CURRENT] = add3(p_particle->m_position[CURRENT], mul3(normalize3(sub3(p_particle->m_position[CURRENT], p_obstacles[i].m_position)),
				p_obstacles[i].m_size / 2 - distance3(p_obstacles[i].m_position, p_particle->m_position[CURRENT]) + DEFAULT_SIZE + Decallage));
			Reflect = mul3(Reflect, p_obstacles->m_friction);
		}
	}

	//Springs
	vec3 f1 = set3(0, 0, 0);
	for (k = 0; k < 4; k++) {
		if (p_particle->m_shear[k] != NULL) {
			op = sub3(p_particle->m_position[CURRENT], p_particle->m_shear[k]->m_position[CURRENT]);
			f1 = add3(mul3(normalize3(op), -K * (norm3(op) - p_particle->l0[2])), f1);
		}
		if (p_particle->m_flexion[k]) {
			op = sub3(p_particle->m_position[CURRENT], p_particle->m_flexion[k]->m_position[CURRENT]);
			f1 = add3(mul3(normalize3(op), -K * (norm3(op) - 2 * p_particle->l0[k % 2])), f1);
		}
		if (p_particle->m_compression[k]) {
			op = sub3(p_particle->m_position[CURRENT], p_particle->m_compression[k]->m_position[CURRENT]);
			f1 = add3(mul3(normalize3(op), -K * (norm3(op) - p_particle->l0[k % 2])), f1);
		}
	}


	//Acceleration
	vec3 Acceleration = div3(add3(add3(add3(add3(Reflect, Gravity), Friction), f1),Parametrage.Wind), p_particle->m_mass);


	//Update speed and position
	p_particle->m_speed[NEXT] = add3(p_particle->m_speed[CURRENT], mul3(Acceleration, p_dt));

	//Friction Ground
	if (!(p_particle->m_position[NEXT].y))
	{
		p_particle->m_speed[NEXT] = mul3(p_particle->m_speed[NEXT], G_FRICTION);
	}
	p_particle->m_position[NEXT] = add3(p_particle->m_position[CURRENT], mul3(p_particle->m_speed[NEXT], p_dt));


	//Touch the ground
	if (p_particle->m_position[NEXT].y<=0)
	{		
		p_particle->m_position[NEXT].y = 0;
		p_particle->m_speed[NEXT].y;
	}

}


/*!<	
 *	\brief	function to finalize the particle update. 
 *
 *	The position & speed calculated in m_position[NEXT] & m_speed[NEXT] are copied into m_position[CURRENT] & m_speed[CURRENT] so the particle can be rendered with its new position.
 *
 *	\param	p_particle	the particle
 */
void finalizeParticle(particle * p_particle)
{
	// TODO
	p_particle->m_position[CURRENT] = p_particle->m_position[NEXT];
	p_particle->m_speed[CURRENT] = p_particle->m_speed[NEXT];

}



/*! 
 *	\brief	to draw the fabric using GL primitives (GL_TRIANGLES / GL_LINE_LOOP)
 *
 *	\param	p_particles	the particles' array to define the position of each particle of the fabric 
 *	\param	p_width		number of particles on the width axis
 *	\param	p_length	number of particles on the length axis
 *	\param	p_obstacles	array of obstacles
 *	\param	p_nbObstacles	number of obstacles in the list
 */
void drawFabric(particle ** p_particles, int p_width, int p_length, obstacle * p_obstacles, int p_nbObstacles)
{
	int i,j;

	GLfloat diff[4] = {1.0f,1.0f,1.0f,1.0f};
	GLfloat spec[4] = {1.0f,1.0f,1.0f,1.0f};

	if(!g_faces)
	{
		g_normals = (vec3*)calloc(sizeof(vec3),2*p_width*p_length);
		g_positions= (vec3*)calloc(sizeof(vec3),2*p_width*p_length);
		g_texcoords = (vec3*)calloc(sizeof(vec3),2*p_width*p_length);
		g_faces = (unsigned int *)calloc(sizeof(unsigned int),12*(p_width-1)*(p_length-1));

		for(i=0; i < (p_width-1)*(p_length-1); i++)
		{
			g_faces[12*i+0+0]	= i/(p_width-1)*p_width + i%(p_width-1);
			g_faces[12*i+0+1]	= i/(p_width-1)*p_width + i%(p_width-1) + 1;
			g_faces[12*i+0+2]	= i/(p_width-1)*p_width + i%(p_width-1) + p_width;

			g_faces[12*i+3+0]	= i/(p_width-1)*p_width + i%(p_width-1) + 1;
			g_faces[12*i+3+1]	= i/(p_width-1)*p_width + i%(p_width-1) + p_width +1;
			g_faces[12*i+3+2]	= i/(p_width-1)*p_width + i%(p_width-1) + p_width;			
			
			g_faces[12*i+6+0]	= p_width*p_length + i/(p_width-1)*p_width + i%(p_width-1) + 1;
			g_faces[12*i+6+1]	= p_width*p_length + i/(p_width-1)*p_width + i%(p_width-1);
			g_faces[12*i+6+2]	= p_width*p_length + i/(p_width-1)*p_width + i%(p_width-1) + p_width;

			g_faces[12*i+9+0]	= p_width*p_length + i/(p_width-1)*p_width + i%(p_width-1) + 1;
			g_faces[12*i+9+1]	= p_width*p_length +i/(p_width-1)*p_width + i%(p_width-1) + p_width;
			g_faces[12*i+9+2]	= p_width*p_length + i/(p_width-1)*p_width + i%(p_width-1) + p_width + 1;
		}
		for(i=0; i < p_width*p_length; i++)
		{
			g_texcoords[i] = set3( (i/p_width)/(float)(p_length-1) , (i%p_width)/(float)(p_width-1) , 0.0f );
			g_texcoords[p_width*p_length+i] = set3( (i/p_width)/(float)(p_length-1) , (i%p_width)/(float)(p_width-1) , 0.0f );
		}

		if(!g_texID)
		{
			g_texID = loadTexture("../tissu/tex.BMP");
		}
	}

	
	for(i=0; i < p_width*p_length; i++)
	{
		g_positions[i] = copy3(p_particles[i%p_width][p_length-1-i/p_width].m_position[CURRENT]);
		g_positions[p_width*p_length+i] = copy3(p_particles[i%p_width][p_length-1-i/p_width].m_position[CURRENT]);
	}
	for(i=0; i < p_width*p_length; i++)
	{
		vec3 n;
		bool valide[4]= {FALSE,FALSE,FALSE,FALSE };


		vec3 v[4];
		if(i%p_width>0)
		{
			v[0] = normalize3(sub3(g_positions[i],g_positions[i-1]));
			valide[0] = TRUE;
		}
		if(i/p_width>0)
		{
			v[1] = normalize3(sub3(g_positions[i],g_positions[i-p_width]));
			valide[1] = TRUE;
		}
		if(i%p_width<p_width-1)
		{
			v[2] = normalize3(sub3(g_positions[i],g_positions[i+1]));
			valide[2] = TRUE;
		}
		if(i/p_width<p_length-1)
		{
			v[3] = normalize3(sub3(g_positions[i],g_positions[i+p_width]));
			valide[3] = TRUE;
		}
		

		n = set3(0.0f,0.0f,0.0f);
		if(valide[0] && valide[1])
			n = add3(n,cross3(v[0],v[1]));
		if(valide[1] && valide[2])
			n = add3(n,cross3(v[1],v[2]));
		if(valide[2] && valide[3])
			n = add3(n,cross3(v[2],v[3]));
		if(valide[3] && valide[0])
			n = add3(n,cross3(v[3],v[0]));

		g_normals[i] = normalize3(n);
		g_normals[p_width*p_length + i] = mul3(g_normals[i],-1.0f);
	}



	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3,GL_FLOAT,0,g_positions);
	glNormalPointer(GL_FLOAT,0,g_normals);
	glTexCoordPointer(3,GL_FLOAT,0,g_texcoords);
	glColorPointer(3,GL_FLOAT,0,g_normals);

	if(g_texID)
	{
		glColor3f(1.0f,1.0f,1.0f);
		glDisable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
	}
	
	glDrawElements(GL_TRIANGLES,12*(p_width-1)*(p_length-1),GL_UNSIGNED_INT,g_faces);

	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);

#ifdef _DEBUG
	for(i=0;i<p_width; i++)
	{
		for(j=0;j<p_length;j++)
		{
			drawSphere(p_particles[i][j].m_position[CURRENT],0.01f,set3(0.5f,0.5f,0.5f));
		}
	}
#endif

	for(i=0;i<p_nbObstacles; i++)
	{	
		drawSphere(p_obstacles[i].m_position,p_obstacles[i].m_size,set3(p_obstacles[i].m_friction/2.0f,0.0f,(1.0f-p_obstacles[i].m_friction)/2.0f));
	}
}
