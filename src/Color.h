#ifndef COLORS_H
#define COLORS_H

#include <SDL2/SDL.h>

static SDL_Color Color(int r, int g, int b)
{
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	return color;
}


#endif // COLORS_H