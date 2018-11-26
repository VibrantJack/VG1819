#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <stdio.h>
#include <stdlib.h>
#include "util\MathUtil.h"
#include "puppy\P_Common.h"
#include "kitten\K_Game.h"

//========================================================================
// This is needed for newer versions of Visual Studio
//========================================================================
FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
//========================================================================


//@TODO move this somewhere not in main lol
void lerp(const float& amount, const glm::vec3& min, const glm::vec3& max, glm::vec3& out)
{
	out = (1 - amount)*min + amount * max;
}

int main( void )
{
    int width, height, x;
    
    
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    if( !glfwOpenWindow( 1280, 720, 0,0,0,0, 24,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        
        glfwTerminate();
        exit( EXIT_FAILURE );
    }
    
#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	glewInit();
#endif

    glfwSetWindowTitle( "VG1819" );
    
    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );
	glEnable(GL_DEPTH_TEST);
	

    // Enable vertical sync (on cards that support it)
    glfwSwapInterval( 0 );
    
	kitten::initGame();

	float lerpVal = 0.5f;
	float changeAmount = 0.009f;
	bool increasing = true;

	glm::vec3 minColour(2.0f / 255.0f, 2.0f / 255.0f, 9.0f / 255.0f);
	glm::vec3 maxColour(135.0f/255.0f, 206.0f/255.0f, 235.0f/255.0f);
	glm::vec3 curColor;
	double deltaTime = 0;
	double oldTime = 0;

    do
	{
		double currentTime = glfwGetTime();
        deltaTime =  currentTime - oldTime;
		oldTime = currentTime;

        glfwGetMousePos( &x, NULL );
        
        // Get window size (may be different than the requested size)
        glfwGetWindowSize( &width, &height );
        
        // Special case: avoid division by zero below
        height = height > 0 ? height : 1;
        
        glViewport( 0, 0, width, height );
        
        // Clear color buffer
		curColor = LERP(lerpVal, minColour, maxColour);
        glClearColor(curColor.x, curColor.y, curColor.z, 0.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
		

		kitten::gameCycle();

        // Swap buffers
        glfwSwapBuffers();
        
		if (increasing)
		{
			lerpVal += changeAmount * deltaTime;
			if (lerpVal > 1.0f)
			{
				increasing = false;
				lerpVal = 1.0f;
			}
		}
		else
		{
			lerpVal -= changeAmount * deltaTime;
			if (lerpVal < 0.0f)
			{
				increasing = true;
				lerpVal = 0.0f;
			}
		}
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
          glfwGetWindowParam( GLFW_OPENED ) );
    
	kitten::shutdownGame();
    // Close OpenGL window and terminate GLFW
	glfwTerminate();
    
    exit( EXIT_SUCCESS );
}


