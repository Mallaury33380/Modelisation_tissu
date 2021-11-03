#ifndef _SIMU_
#define _SIMU_

#include "utils.h"


/*!
 *	\brief to initialize the simulation & the rendering
 */
void init();

/*!
 *	\brief	to process the render loop
 *
 *	\param p_window	the handle of the window in which the rendering will be done
 */
void renderLoop(SDL_Window * p_window);


/*!
 *	\brief to manage the events
 *
 *	\return		1 if application should quit, 0 else
 */
bool events();

/*!
 *	\brief	to update the simulation
 *
 *	\param p_dt time elapsed since last call
 */
void update(float p_dt);

/*! 
 *	\brief do the rendering of the scene
 */
void render();

#endif