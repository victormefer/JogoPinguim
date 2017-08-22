#ifndef ALIEN_H
#define ALIEN_H

#include "Game.h"
#include "GameObject.h"
#include "Geometria.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Bullet.h"
#include "StillAnimation.h"
#include "Timer.h"
#include "Penguins.h"
#include "Sound.h"
#include <vector>
#include <queue>
#include <cstdlib>

#define ALIEN_SPEED 350 // pixels per second
#define ALIEN_ROTATION_SPEED 150 // degrees per second
#define DISTANCE_MINION_ALIEN 100 // pixels
#define MINION_SPEED 150 // degrees per second
#define ALIEN_BULLET_SPEED 500 // pixels per second
#define ALIEN_MAX_BULLET_DISTANCE 1000 // pixels

class Minion : public GameObject
{
public:
	Minion(GameObject* minionCenter, float arcOffset = 0, float scale = 1);
	~Minion();

	void Update(float dt);
	void Render();
	bool IsDead();

	void NotifyCollision(const GameObject& other);
	bool Is(std::string type) const;

	void Shoot(Point pos);

	void Die();

private:
	GameObject* center;
	Sprite sp;
	float arc;
};



class Alien : public GameObject
{
public:
	Alien(float x, float y, int nMinions);
	~Alien();

	void Update(float dt);
	void Render();
	bool IsDead();

	void NotifyCollision(const GameObject& other);
	bool Is(std::string type) const;

	void Die();

	static int alienCount;

private:

	class Action
	{
	public:
		enum ActionType{ MOVE, SHOOT };
		Action(ActionType type, float x, float y);

		ActionType type;
		Point pos;
	};

	enum AlienState{ MOVING, RESTING };

	AlienState alienState;
	Timer shootCooldown;

	Sprite sp;
	Point speed;
	int hp;
	float ALIEN_SHOOT_COOLDOWN;

	std::queue<Action> taskQueue;
	std::vector<Minion> minionArray;
};



#endif // ALIEN_H