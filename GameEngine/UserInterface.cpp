/*
#include "OpenGLWrapper.h"
#include "Azul.h"
#include "MathEngine.h"
#include "Camera.h"
#include "UserInterface.h"

#include <stdio.h>
*/
#include "AzulCore.h"


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	AZUL_UNUSED( scancode );
	AZUL_UNUSED( mods );
	KeyAction( window,  key,  action);
}

static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	AZUL_UNUSED( mods );
	MouseAction( window,  button,  action);
}

static void cursor_callback(GLFWwindow* window, double x_pos, double y_pos)
{
	CursorPosition( window,  (float)x_pos,  (float)y_pos);
}

static void cursor_active_callback(GLFWwindow* window, int enter)
{
	CursorInView( window,  enter);
}



//initialize the input callback system
void initInputInterface(GLFWwindow* window, bool &joystics)
{
	AZUL_UNUSED( joystics );

	//initializing keyboard
	glfwSetKeyCallback(window, key_callback);

	//initializing mouse
	glfwSetMouseButtonCallback(window, mouse_callback);
	glfwSetScrollCallback(window, cursor_callback);
	//init mouse cursor 
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetCursorEnterCallback(window, cursor_active_callback);


	//check for joystics and return
	int joyNum = 1;
	int count[12];

	while(glfwJoystickPresent(joyNum) == GL_TRUE)
	{
		memcpy(joystick1.AxesPositions, glfwGetJoystickAxes( GLFW_JOYSTICK_1,count ),sizeof(float)*12);
		
		joyNum++;
	}
}


void KeyAction(GLFWwindow* window, int key, int action)
{
	window;
	key;
	action;


//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, GL_TRUE);
//
//
//	float delta_z = 0.0f;
//
//	if(key == GLFW_KEY_UP)
//   {
//		delta_z = 1.0f;
//   }
//
//	if(key == GLFW_KEY_DOWN)
//	{
//		delta_z = -1.0f;
//   }
//
//
//
//	Vect A;
//	pCamera->getPos( A );
//
////	A[z] += delta_z;
//
//	Vect UP;
//	pCamera->getUp(UP);
//	pCamera->setOrientAndPosition( UP, Vect(0.0f,0.0f,0.0f), A );
//
//	
	//printf("A: %f %f %f\n",A[x],A[y],A[z]);

	//printf("\n");

}



void MouseAction(GLFWwindow* window,int  button,int  action)
{
	AZUL_UNUSED( window );
	AZUL_UNUSED( button );
	AZUL_UNUSED( action );
}



void CursorPosition(GLFWwindow* window, float x_pos, float y_pos)
{
	AZUL_UNUSED( window );
	AZUL_UNUSED( x_pos );
	AZUL_UNUSED( y_pos );
}


void CursorInView(GLFWwindow* window, int enter)
{
	AZUL_UNUSED( window );
	AZUL_UNUSED( enter );
}


///////////////////////////////////////////////////////////////////////////////
// Window has changed size, or has just been created. In either case, we need
// to use the window dimensions to set the viewport and the projection matrix.
void ChangeSize(int w, int h)
{

	w = 800;
	h = 600;
	// set the view port
	Camera::setViewport(0, 0, w, h);
	// set the perspective
	Camera::setPerspective( 35.0f, float(w)/float(h), 1.0f, 500.0f);

	// position the camera   (up,lookat, pos)
	//Camera::setOrientAndPosition( Vect(0.0f,1.0f,0.0f), Vect(0.0f,0.0f,-1.0f), Vect(0.0f,0.0f,7.0f) );

}