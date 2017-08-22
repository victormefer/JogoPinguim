#ifndef SPRITE_H
#define SPRITE_H

#include "Camera.h"
#include "Geometria.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <memory>

class Resources;

class Sprite
{

public:

	Sprite();
	Sprite(const char* file, int frameCount = 1, float frameTime = 1);
	~Sprite();

	void Open(const char* file);
	void SetClip(int x, int y, int w, int h);
	void Render(int x, int y, float angle = 0);
	void Update(float dt);

	int GetWidth();
	int GetHeight();
	bool IsOpen();

	void SetScaleX(float scale);
	void SetScaleY(float scale);

	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);

private:

	std::shared_ptr<SDL_Texture> texture;
	int width;
	int height;
	SDL_Rect clipRect;

	float scaleX, scaleY;

	int frameCount, currentFrame;
	float timeElapsed, frameTime;
};

#include "Game.h"
#include "Resources.h"

#endif // SPRITE_H