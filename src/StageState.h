#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "State.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Geometria.h"
#include "InputManager.h"
#include "Camera.h"
#include "Penguins.h"
#include "Alien.h"
#include "Collision.h"
#include "Tile.h"
#include "Music.h"
#include "StateData.h"
#include "Timer.h"
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <memory>

class StageState : public State
{

public:
	StageState();
	~StageState();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

private:
	Sprite bg;
	Music bgMusic;
	TileSet* tileSet;
	TileMap* tileMap;
	GameObject *alien[3], *penguins;
	bool endGame, endVictory;
	Timer end;
};

#include "EndState.h"

#endif // STAGESTATE_H