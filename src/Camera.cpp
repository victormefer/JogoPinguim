#include "Camera.h"

Point Camera::pos;
Point Camera::speed;
GameObject* Camera::focus;

/* ************************************************************
 *
 * Novo foco para a camera
 *
 *************************************************************/
void Camera::Follow(GameObject* newFocus)
{
	focus = newFocus;
}


/* ************************************************************
 *
 * Retira foco da camera
 *
 *************************************************************/
void Camera::Unfollow()
{
	focus = NULL;
}


/* ************************************************************
 *
 * Atualiza tela a partir do foco ou do deltatime
 *
 *************************************************************/
void Camera::Update(float dt)
{
	if (focus != NULL)
	{
		pos = focus->box.Center() + Point(-512, -300);
	}
	else
	{
		if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
		{
			speed = Point(-CAMERA_SPEED * dt, 0);
			pos = pos + speed;
		}
		if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
		{
			speed = Point(CAMERA_SPEED * dt, 0);
			pos = pos + speed;
		}
		if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY))
		{
			speed = Point(0, -CAMERA_SPEED * dt);
			pos = pos + speed;
		}
		if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))
		{
			speed = Point(0, CAMERA_SPEED * dt);
			pos = pos + speed;
		}
	}
}