#include "Penguins.h"

// Variavel estatica
Penguins* Penguins::player;


/* ************************************************************
 *
 * Construtor penguin
 *
 *************************************************************/
Penguins::Penguins(float x, float y) : bodySp("img/penguin.png"), cannonSp("img/cubngun.png"), speed(), timer()
{
	box = Rect(x, y, bodySp.GetWidth(), bodySp.GetHeight());
	linearSpeed = 0.0;
	cannonAngle = 0.0;
	hp = 50;
	player = this;
}



/* ************************************************************
 *
 * Destrutor penguin
 *
 *************************************************************/
Penguins::~Penguins()
{
	player = NULL;
}



/* ************************************************************
 *
 * Update penguin
 *
 *************************************************************/
void Penguins::Update(float dt)
{
	bool pressing = false;
	timer.Update(dt);

	if (InputManager::GetInstance().IsKeyDown('w'))
	{
		pressing = true;
		if ( linearSpeed < MAX_SPEED * dt )
			// v = v0 + at, modulo da velocidade
			linearSpeed = linearSpeed + PENGUIN_ACCELERATION * dt;
		else
			linearSpeed = MAX_SPEED * dt;
		speed = Point( ProjectX(linearSpeed, rotation), ProjectY(linearSpeed, rotation) );
	}

	if (InputManager::GetInstance().IsKeyDown('s'))
	{
		pressing = true;
		if ( linearSpeed > -MAX_SPEED * dt )
			// v = vo + at, modulo da velocidade
			linearSpeed = linearSpeed - PENGUIN_ACCELERATION * dt;
		else
			linearSpeed = -MAX_SPEED * dt;
		speed = Point( ProjectX(linearSpeed, rotation), ProjectY(linearSpeed, rotation) );
	}

	// Velocidade tende a zero se não pressionar nenhum botão de aceleração
	if (!pressing)
	{
		if (linearSpeed > 0)
		{
			linearSpeed -= PENGUIN_ACCELERATION * dt;
			if (linearSpeed < PENGUIN_ACCELERATION * dt)
				linearSpeed = 0.0;
		}
		else
		{
			linearSpeed += PENGUIN_ACCELERATION * dt;
			if (linearSpeed > -PENGUIN_ACCELERATION * dt)
				linearSpeed = 0.0;
		}
		speed = Point( ProjectX(linearSpeed, rotation), ProjectY(linearSpeed, rotation) );
	}


	if (InputManager::GetInstance().IsKeyDown('a'))
	{
		rotation -= PENGUIN_ROTATION_SPEED * dt;
	}

	if (InputManager::GetInstance().IsKeyDown('d'))
	{
		rotation += PENGUIN_ROTATION_SPEED * dt;
	}

	box = box + speed;
	if (box.x < 0)
		box.x = 0;
	else if (box.x + box.w > 1408)
		box.x = 1408 - box.w;
	if (box.y < 0)
		box.y = 0;
	else if (box.y + box.h > 1280)
		box.y = 1280 - box.h;

	cannonAngle = LineInclination( box.Center(), Point( InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY() ) );

	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) && timer.Get() >= SHOOT_COOLDOWN)
	{
		Shoot();
		timer.Restart();
	}

}



/* ************************************************************
 *
 * Render penguin
 *
 *************************************************************/
void Penguins::Render()
{
	bodySp.Render(box.x, box.y, rotation);
	cannonSp.Render( box.x - ((box.w - cannonSp.GetWidth()) / 2), box.y + ((box.h - cannonSp.GetHeight()) / 2), cannonAngle );
}



/* ************************************************************
 *
 * Is Dead penguin
 *
 *************************************************************/
bool Penguins::IsDead()
{
	return hp == 0 ? true : false;
}


/* ************************************************************
 *
 * Type Penguins
 *
 *************************************************************/
bool Penguins::Is(std::string type) const
{
	return (type == "Penguins");
}



/* ************************************************************
 *
 * Atirar
 *
 *************************************************************/
void Penguins::Shoot()
{
	Point bulletStart = Point(cannonSp.GetWidth() / 2, 0);
	bulletStart.Rotate(cannonAngle);
	bulletStart = bulletStart + box.Center();
	Bullet* bullet = new Bullet(bulletStart.x, bulletStart.y, cannonAngle, BULLET_SPEED, MAX_BULLET_DISTANCE, false, "img/penguinBullet.png", 4, 0.06);
	Game::GetInstance().GetCurrentState().AddObject(bullet);
}



/* ************************************************************
 *
 * Colisao Penguins
 *
 *************************************************************/
void Penguins::NotifyCollision(const GameObject& other)
{
	if (other.Is("Bullet"))
	{
		Bullet& bullet = (Bullet&)other;
		if ( bullet.targetsPlayer )
		{
			hp -= 10;
			if (hp <= 0)
			{
				Sound boom = Sound("audio/boom.wav");
				boom.Play(0);

				Sprite sprite = Sprite("img/penguindeath.png", 5, 0.08);
				StillAnimation* death = new StillAnimation(box.Center().x - sprite.GetWidth() / 2, box.Center().y - sprite.GetHeight() / 2, 0, sprite, 0.4, true);
				Game::GetInstance().GetCurrentState().AddObject(death);
			}
		}
	}
}


