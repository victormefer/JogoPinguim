#ifndef PENGUINS_H
#define PENGUINS_H

#include "GameObject.h"
#include "Bullet.h"
#include "Geometria.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Timer.h"
#include "StillAnimation.h"
#include <cmath>


#define PENGUIN_ACCELERATION 10 // pixels per second square
#define MAX_SPEED 400 // pixels per second
#define PENGUIN_ROTATION_SPEED 180 // pixels per second
#define BULLET_SPEED 600 // pixels per second
#define MAX_BULLET_DISTANCE 1000 // pixels
#define SHOOT_COOLDOWN 1 // seconds

class Penguins : public GameObject
{
public:
	Penguins(float x, float y);
	~Penguins();

	void Update(float dt);
	void Render();
	bool IsDead();
	
	void NotifyCollision(const GameObject& other);
	bool Is(std::string type) const;

	void Shoot();

	static Penguins* player;

private:
	Sprite bodySp, cannonSp;
	Point speed;
	float linearSpeed, cannonAngle;
	int hp;
	Timer timer;
};



#endif // PENGUINS_H