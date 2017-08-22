#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>
#include <memory>
#include "Resources.h"

class Sound
{
public:
	Sound();
	Sound(const char* file);

	void Play(int times);
	void Stop();

	void Open(const char* file);
	bool IsOpen();

private:
	std::shared_ptr<Mix_Chunk> chunk;
	int channel;
};


#endif // SOUND_H