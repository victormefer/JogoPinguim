#include "TitleState.h"

/* ************************************************************
 *
 * Construtor
 *
 *************************************************************/
TitleState::TitleState() : text("font/Call me maybe.ttf", 24, Text::BLENDED, "PRESS SPACE BAR TO START THE GAME", Color(0, 0, 0))
{
	bg = Sprite("img/title.jpg");
	text.SetPos(512, 500, true, true);
	textBlink = Timer();
	blink = true;
}


/* ************************************************************
 *
 * Update
 *
 *************************************************************/
void TitleState::Update(float dt)
{
	if ( InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY) )
		quitRequested = true;
	if (InputManager::GetInstance().KeyPress(SPACE_BAR))
	{
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
void TitleState::Render()
{
	bg.Render(0, 0);
	if (blink)
		text.Render();
}


/* ************************************************************
 *
 * Pause
 *
 *************************************************************/
void TitleState::Pause(){}


/* ************************************************************
 *
 * Resume
 *
 *************************************************************/
void TitleState::Resume()
{
	Camera::pos = Point();
}

