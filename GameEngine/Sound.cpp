#include "Sound.h"


Sound::Sound()
{
	soundEngine = createIrrKlangDevice();
}

Sound * Sound::privInstance()
{
	static Sound instance;
	return &instance;
}

ISoundEngine * Sound::getSoundEngine()
{
	return privInstance()->soundEngine;
}

void Sound::Clear()
{
	privInstance()->getSoundEngine()->removeAllSoundSources();
}

void Sound::unload()
{
	privInstance()->soundEngine->drop();
}