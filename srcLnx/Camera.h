#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Geometria.h"
#include "InputManager.h"

#define CAMERA_SPEED 300 // pixels per second

class Camera
{
public:
	static void Follow(GameObject* newFocus);
	static void Unfollow();
	static void Update(float dt);

	static Point pos;
	static Point speed;

private:
	static GameObject* focus;

};



#endif // CAMERA_H