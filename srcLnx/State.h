#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "GameObject.h"
#include "Geometria.h"
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <memory>

class State
{
public:
	State();
	virtual ~State();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	void AddObject(GameObject*);

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	bool PopRequested();
	bool QuitRequested();

protected:
	virtual void UpdateArray(float dt);
	virtual void RenderArray();

	bool quitRequested, popRequested;

	std::vector<std::unique_ptr<GameObject>> objectArray;
};


#endif // STATE_H