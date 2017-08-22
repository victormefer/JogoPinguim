#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Geometria.h"
#include "Sprite.h"


class Bullet : public GameObject
{
public:
	Bullet(float x, float y, float angle, float speed, float maxDistance, bool targetsPlayer, const char* sprite, int frameCount = 1, float frameTime = 1);
	~Bullet();

	void Update(float dt);
	void Render();
	bool IsDead();
	
	void NotifyCollision(const GameObject& other);
	bool Is(std::string type) const;

	bool targetsPlayer;

private:
	Sprite sp;
	Point speed;
	float distanceLeft;
};



#endif // BULLET_H