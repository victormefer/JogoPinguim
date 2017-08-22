#include "Bullet.h"


/* ************************************************************
 *
 * Construtor bullet
 *
 *************************************************************/
Bullet::Bullet(float x, float y, float angle, float speed, float maxDistance, bool targetsPlayer, const char* sprite, int frameCount, float frameTime)
{
	sp = Sprite(sprite, frameCount, frameTime);
	box = Rect(x - sp.GetWidth() / 2, y - sp.GetHeight() / 2, sp.GetWidth(), sp.GetHeight());
	rotation = angle;
	this->speed = Point( ProjectX(speed, angle), ProjectY(speed, angle) );
	distanceLeft = maxDistance;
	this->targetsPlayer = targetsPlayer;
}


/* ************************************************************
 *
 * Destrutor bullet
 *
 *************************************************************/
Bullet::~Bullet(){}


/* ************************************************************
 *
 * Update bullet
 *
 *************************************************************/
void Bullet::Update(float dt)
{
	Point previous = box.Center();
	box.x += speed.x * dt;
	box.y += speed.y * dt;
	distanceLeft -= Distance(box.Center(), previous);
	sp.Update(dt);
}



/* ************************************************************
 *
 * Render bullet
 *
 *************************************************************/
void Bullet::Render()
{
	sp.Render(box.x, box.y, rotation);
}



/* ************************************************************
 *
 * Bullet morre se ja percorreu a distancia maxima
 *
 *************************************************************/
bool Bullet::IsDead()
{
	return distanceLeft > 0 ? false : true;
}


/* ************************************************************
 *
 * Type Bullet
 *
 *************************************************************/
bool Bullet::Is(std::string type) const
{
	return (type == "Bullet");
}


/* ************************************************************
 *
 * Colisao Bullet
 *
 *************************************************************/
void Bullet::NotifyCollision(const GameObject& other)
{
	if (other.Is("Alien") && !targetsPlayer)
		distanceLeft = 0.0;
	else if (other.Is("Penguins") && targetsPlayer)
		distanceLeft = 0.0;
}