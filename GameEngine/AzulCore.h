#ifndef AZULCORE_H
#define AZULCORE_H

#include "AzulHeader.h"

struct GLFWwindow;

class AzulCore : public Engine
{

public:

	AzulCore();

	void Initialize();
	void LoadContent();
	void Update();
	void Draw();
	void UnLoadContent();
	static void clearTrails();
	static Engine *getEngine();
	static void setTargetAndSpeed(float x, float y, float z, float s);

	void cameraMove();
private:
	void SetupRC();
	void ShutdownRC(GLFWwindow* window);

	static AzulCore *privInstance();
	
	GLFWwindow * window;
	bool joystickActive;
};


GLFWwindow* createGraphicsWindow( const char* windowName, const int Width,const int Height );

#endif 