#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL_mixer.h>
#include <memory>
#include "Resources.h"

class Music
{
public:
	Music();
	Music(const char* file);

	void Play(int times);
	void Stop();

	void Open(const char* file);
	bool IsOpen();

private:
	std::shared_ptr<Mix_Music> music;

};


#endif // MUSIC_H