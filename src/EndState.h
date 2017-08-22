#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "Game.h"
#include "State.h"
#include "StateData.h"
#include "StageState.h"
#include "Timer.h"
#include "Text.h"
#include "Color.h"

#define BLINK_TIME 0.5 // seconds

class EndState : public State
{
public:
	EndState(StateData stateData);
	~EndState();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

private:
	Sprite bg;
	Music music;
	Text instructions;
	Timer textBlink;
	bool blink;
};



#endif // ENDSTATE_H