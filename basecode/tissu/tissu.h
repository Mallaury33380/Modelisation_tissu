#ifndef _TISSU_
#define _TISSU_

#include "./vec3/include/vec3.h"
#include "utils.h"

#define EULER_IMPLICITE

/*! To define the height of the fabric at the beginning */
#define BEGIN_HEIGHT 1

/*! To define the index of the current value (position/speed of the particle) */
#define CURRENT	0
/*! to define the index of the calculated value (next value for position & speed of the particle) */
#define NEXT	1

/*! Coefficient for friction (for the particle) */
#define FRICTION	10.0f
/*! Coefficient to tweak the spring reactions easily */
#define K			150.0f
/*! Coefficient for obstacle friction */
#define OBSTACLE_FRICTION 10.0f

/*! Gravity value (to be applied on Y axis) */
#define GRAVITY		-0.81f
/*! integration step to have same behaviour on different machines */
#define INTEGRATION_STEP	0.005f

/*! Default size */
#define DEFAULT_SIZE	0.005f
/*! Default mass */
#define DEFAULT_MASS	0.50f

/*! Obstacle Elasticity*/
#define ELASTICITY  0.5f
/*! Coeff Size Object*/
#define SIZE_OBSTACLE  200.0f  //Release 200.0f

/*! Coff Friction Ground*/
#define G_FRICTION 0.1f

/*! Space for the flag*/
#define SPACE 0.5f
#define CLEAR_OBSTACLE -5.0f

/*! Step for wind*/
#define WIND_STEP 0.1f
/*! Limit of WIND*/
#define WIND_LIMIT 2.0f

/*! Medusa*/
#define MEDUSA_STEP 10.0f
#define COEFF_MEDUSA 0.995f
#define MEDUSA_LIMIT 10.0f
#define MEDUSA_FLY 1.0f




/*! Definition of a particle properties */
typedef struct sParticle{

	//TODO
	int m_ID;
	float m_mass;
	bool m_canMove;
	float	m_size;			/*! size of the particle (diameter) */
	vec3	m_position[2];	/*! position of the particle (CURRENT & NEXT), m_position[CURRENT] is used for rendering, m_position[NEXT] is used for calculation */
	vec3	m_speed[2];		/*! speed of the particle (CURRENT & NEXT) */
	struct sParticle* m_compression[4];	//Voisins compression
	struct sParticle* m_shear[4];		//Voisins cisaillement	
	struct sParticle* m_flexion[4];		//Voisins flexion
	float m_friction;
	float l0[3];
	
	//TODO
}particle;


/*! definition of the type to store a sphere/obstacle configuration */
typedef struct sObstacle {
	vec3	m_position;
	float	m_size;
	float	m_friction;
}obstacle;


/*! definition parametrage*/
typedef struct sParametrage
{
	vec3 Wind;
	int Gravity;
	int Flag;
	int Medusa[2];
}parametrage;




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
void initializeArrayOfParticles(particle ** p_array, float p_width, float p_length, int p_nbPartW, int p_nbPartL, obstacle * p_obstacles, int p_nbObstacles);


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
particle ** createFabric(float p_width, float p_length, int p_nbPartW, int p_nbPartL, obstacle * p_obstacles, int p_nbObstacles);

/*!<	
 *	\brief	function to delete the fabric particles created before
 *
 *	\param	p_array		the particles
 *	\param	p_nbPartW	number of particles on width axis
 *	\param	p_nbPartL	number of particles on length axis
 */
void deleteFabric(particle ** p_array, int p_nbPartW, int p_nbPartL);


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
particle createParticle(int p_num, float p_mass, float p_size, bool p_static, vec3 p_pos, vec3 p_speed, float p_friction);

/*!<	
 *	\brief	function to update all the fabric particles 
 *
 *	\param	p_array		the particles
 *	\param	p_nbPartW	number of particles on width axis
 *	\param	p_nbPartL	number of particles on length axis
 *	\param	p_dt		the elapsed time to integrate the acceleration to calculate speed & position for each particle*
 *	\param	p_obstacles	the obstacles to take into account in the simulation (array of obstacle structures)
 *	\param	p_nbObstacles	the number of obstacles stored in the array "p_obstacles"
 */
void updateFabric(particle ** p_array, int p_nbPartW, int p_nbPartL, float p_dt, obstacle * p_obstacles, int p_nbObstacles);

/*!<	
 *	\brief	function to update a particle
 *
 *	\param	p_particle	the particle
 *	\param	p_dt		the elapsed time to integrate the acceleration to calculate speed & position for the particle
 *	\param	p_obstacles	the obstacles to take into account in the simulation (array of obstacle structures)
 *	\param	p_nbObstacles	the number of obstacles stored in the array "p_obstacles"
 */
void updateParticle(particle * p_particle, float p_dt, obstacle * p_obstacles, int p_nbObstacles);



/*!<	
 *	\brief	function to finalize the particle update. 
 *
 *	The position & speed calculated in m_position[NEXT] & m_speed[NEXT] are copied into m_position[CURRENT] & m_speed[CURRENT] so the particle can be rendered with its new position.
 *
 *	\param	p_particle	the particle
 */
void finalizeParticle(particle * p_particle);


/*! 
 *	\brief	to draw the fabric using GL primitives (GL_TRIANGLES / GL_LINE_LOOP)
 *
 *	\param	p_particles	the particles' array to define the position of each particle of the fabric 
 *	\param	p_width		number of particles on the width axis
 *	\param	p_length	number of particles on the length axis
 *	\param	p_obstacles	array of obstacles
 *	\param	p_nbObstacles	number of obstacles in the list
 */
void drawFabric(particle ** p_particles, int p_width, int p_length, obstacle * p_obstacles, int p_nbObstacles);






#endif