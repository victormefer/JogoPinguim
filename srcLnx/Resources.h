#ifndef RESOURCES_H
#define RESOURCES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>
#include "Excecoes.h"
#include "Game.h"

class Resources
{
public:
	static SDL_Texture* GetImage(const char* file);
	static void ClearImages();

private:
	static std::unordered_map<std::string, SDL_Texture*> imageTable;

};


#endif // RESOURCES_H