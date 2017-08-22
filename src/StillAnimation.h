#ifndef STILLANIMATION_H
#define STILLANIMATION_H

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class StillAnimation : public GameObject
{
public:
	StillAnimation(float x, float y, float rotation, Sprite sprite, float timeLimit, bool ends);
	~StillAnimation(){}

	void Update(float dt);
	void Render();
	bool IsDead();

	void NotifyCollision(const GameObject& other);
	bool Is(std::string type) const;

private:
	Timer endTimer;
	float timeLimit;
	bool oneTimeOnly;
	Sprite sp;

};


#endif // STILLANIMATION_H