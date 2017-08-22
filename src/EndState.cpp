#include "EndState.h"

/* ************************************************************
 *
 * Construtor
 *
 *************************************************************/
EndState::EndState(StateData stateData) : instructions("font/Call me maybe.ttf", 24, Text::BLENDED, "PRESS SPACE BAR TO TRY AGAIN, ESC TO RETURN TO THE MENU", Color(0, 0, 0))
{
	if (stateData.playerVictory)
	{
		bg = Sprite("img/win.jpg");
		music = Music("audio/endStateWin.ogg");
	}
	else
	{
		bg = Sprite("img/lose.jpg");
		music = Music("audio/endStateLose.ogg");
	}
	music.Play(0);
	instructions.SetPos(512, 500, true, true);
	textBlink = Timer();
	blink = true;
}

/* ************************************************************
 *
 * Destrutor
 *
 *************************************************************/
EndState::~EndState()
{
	music.Stop();
}


/* ************************************************************
 *
 * Update
 *
 *************************************************************/
void EndState::Update(float dt)
{
	if (InputManager::GetInstance().QuitRequested())
		quitRequested = true;
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY))
	{
		popRequested = true;
	}
	if (InputManager::GetInstance().KeyPress(SPACE_BAR))
	{
		popRequested = true;
		StageState* stage = new StageState();
		Game::GetInstance().Push(stage);
	}
	if (textBlink.Get() >= BLINK_TIME)
	{
		textBlink.Restart();
		blink = blink ? false : true;
	}
	textBlink.Update(dt);
}


/* ************************************************************
 *
 * Render
 *
 *************************************************************/
void EndState::Render()
{
	bg.Render(0, 0);
	if (blink)
		instructions.Render();
}


/* ************************************************************
 *
 * Pause
 *
 *************************************************************/
void EndState::Pause(){}


/* ************************************************************
 *
 * Resume
 *
 *************************************************************/
void EndState::Resume(){}

