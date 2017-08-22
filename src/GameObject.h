#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Geometria.h"
#include <string>

class GameObject
{
public:
	GameObject() {rotation = 0;}
	virtual ~GameObject() {}

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;

	virtual void NotifyCollision(const GameObject& other) = 0;
	virtual bool Is(std::string type) const = 0;

	Rect box;

	float rotation;
};


#endif // GAMEOBJECT_H