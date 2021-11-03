#include "utils.h"
#include <stdio.h>
#include "simu.h"
#include "tissu.h"

/*! extern parametrage*/
parametrage Parametrage;



/*!
 *	\brief A simple function that prints a message, the error code returned by SDL,and quits the application 
 *
 *	\param	p_msg	the message to display
 */
void sdldie(const char *p_msg)
{
    printf("%s: %s\n", p_msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}
 
/*!
 *	\brief display SDL Error 
 *
 *	\param	p_line	the line number
 */
void checkSDLError(int p_line)
{
#ifndef _DEBUG
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		printf("SDL Error: %s\n", error);
		if (p_line != -1)
			printf(" + line: %i\n", p_line);
		SDL_ClearError();
	}
#endif
}
 
 
/* Our program's entry point */
int main(int argc, char *argv[])
{
	//Initialisation Parametrage
	Parametrage.Flag = 0;
	Parametrage.Gravity = 1;
	Parametrage.Wind = set3(0, 0, 0);
	
	
	
	
	SDL_Window *mainwindow; /* Our window handle */
    SDL_GLContext maincontext; /* Our opengl context handle */
	unsigned char quit = 0; /* to know if app should quit */

 
	srand((unsigned)time(NULL));
	 
	/* Set the render mode in compatibility profile */
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    /* Request opengl 3.2 context.
     * SDL doesn't have the ability to choose which profile at this time of writing,
     * but it should default to the core profile */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);


    if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
        sdldie("Unable to initialize SDL"); /* Or die on error */
 
 
    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
 
    /* Create our window centered at 512x512 resolution */
	mainwindow = SDL_CreateWindow("Fabric simulation", SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, 1024, 1024, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if (!mainwindow) /* Die if creation failed */
        sdldie("Unable to create window");
 
    checkSDLError(__LINE__);
 
    /* Create our opengl context and attach it to our window */
    maincontext = SDL_GL_CreateContext(mainwindow);
    checkSDLError(__LINE__);
 
 
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
 
	/* Run the render loop */
	renderLoop(mainwindow);

	/* Delete our opengl context, destroy our window, and shutdown SDL */
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();

	return 0;
}