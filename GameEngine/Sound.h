#ifndef AUDIO_H
#define AUDIO_H

#include "Audio/include/irrKlang.h"
//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace irrklang;

class Sound
{
public:
	static ISoundEngine * getSoundEngine();
	static void unload();
	static void Clear();

private:
	static Sound * privInstance();
	Sound();

	ISoundEngine * soundEngine;

};


#endif