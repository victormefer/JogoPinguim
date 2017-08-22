#include "StillAnimation.h"


/* ************************************************************
 *
 * Construtor
 *
 *************************************************************/
StillAnimation::StillAnimation(float x, float y, float rotation, Sprite sprite, float timeLimit, bool ends)
{
	sp = sprite;
	box = Rect(x, y, sp.GetWidth(), sp.GetHeight());
	this->rotation = rotation;
	this->timeLimit = timeLimit;
	oneTimeOnly = ends;
	if (ends)
		endTimer = Timer();
}



/* ************************************************************
 *
 * Update
 *
 *************************************************************/
void StillAnimation::Update(float dt)
{
	sp.Update(dt);
	if (oneTimeOnly)
		endTimer.Update(dt);
}



/* ************************************************************
 *
 * Render
 *
 *************************************************************/
void StillAnimation::Render()
{
	sp.Render(box.x, box.y, rotation);
}



/* ************************************************************
 *
 * IsDead
 *
 *************************************************************/
bool StillAnimation::IsDead()
{
	if (oneTimeOnly)
	{
		if (endTimer.Get() <= timeLimit)
			return false;
		else
			return true;
	}
	else
		return false;
}



/* ************************************************************
 *
 * IsDead
 *
 *************************************************************/
bool StillAnimation::Is(std::string type) const
{
	return (type == "StillAnimation");
}



/* ************************************************************
 *
 * Colisão
 *
 *************************************************************/
void StillAnimation::NotifyCollision(const GameObject& other){}