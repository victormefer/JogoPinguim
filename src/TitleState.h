#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.h"
#include "Game.h"
#include "Sprite.h"
#include "StageState.h"
#include "InputManager.h"
#include "Camera.h"
#include "Text.h"
#include "Timer.h"
#include "Color.h"

#define BLINK_TIME 0.5 // seconds

class TitleState : public State
{
public:
	TitleState();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

private:
	Sprite bg;
	Text text;
	Timer textBlink;
	bool blink;
};



#endif // TITLESTATE_H