#include "Alien.h"


int Alien::alienCount;

/* ************************************************************
 *
 * Construtor
 *
 *************************************************************/
Alien::Alien(float x, float y, int nMinions)
{
	sp = Sprite("img/alien.png");
	box = Rect(x, y, sp.GetWidth(), sp.GetHeight());
	speed = Point(0, 0);
	hp = 30;
	alienState = RESTING;
	shootCooldown = Timer();
	int rnd = rand() % 25;
	ALIEN_SHOOT_COOLDOWN = 1.0 + (float)rnd / 10.0;

	// Popular array de minions
	for (int i = 0; i < nMinions; i++)
	{
		int rnd = rand() % 50;
		float scale = 1 + (float)rnd / 100;
		Minion minion = Minion(this, 360 / nMinions * i, scale);
		minionArray.emplace_back(minion);
	}

	alienCount++;
}


/* ************************************************************
 *
 * Destrutor
 *
 *************************************************************/
Alien::~Alien()
{
	alienCount--;
}


/* ************************************************************
 *
 * Construtor Action
 *
 *************************************************************/
Alien::Action::Action(ActionType type, float x, float y)
{
	pos = Point(x, y);
	this->type = type;
}


/* ************************************************************
 *
 * Update
 *
 *************************************************************/
void Alien::Update(float dt)
{
	// Checar se houve input do mouse

	if (alienState == RESTING)
	{
		shootCooldown.Update(dt);
		if (shootCooldown.Get() > ALIEN_SHOOT_COOLDOWN)
		{
			if (Penguins::player != NULL)
			{
				// Alien para num angulo aleatorio a 200 pixels do player
				int rnd = rand() % 360;
				Point finalPos = Point(200, 0);
				finalPos.Rotate(rnd);
				finalPos = finalPos + Penguins::player->box.Center();
				taskQueue.emplace( Action(Action::MOVE, finalPos.x, finalPos.y) );
				alienState = MOVING;
			}
		}
	}
	else
	{
		// Realiza uma ação da fila
		if (!taskQueue.empty())
		{
			// Ação de mover
			if (taskQueue.front().type == Action::MOVE)
			{
				// Calcular componentes x e y da velocidade a partir de um modulo constante
				float angle = LineInclination(box.Center(), taskQueue.front().pos);
				speed = Point( ProjectX(ALIEN_SPEED, angle) * dt, ProjectY(ALIEN_SPEED, angle) * dt );
				box = box + speed;

				// Se centro do alien está dentro de um range em volta do ponto final da ação
				if ( Distance(taskQueue.front().pos, box.Center()) < ALIEN_SPEED * dt )
				{
					// Colocar alien na posicao final
					box.x = taskQueue.front().pos.x - box.w / 2;
					box.y = taskQueue.front().pos.y - box.h / 2;
					// Retira ação de mover da fila
					taskQueue.pop();
					// Atira no player
					if (Penguins::player != NULL)
					{
						taskQueue.emplace( Action(Action::SHOOT, Penguins::player->box.Center().x, Penguins::player->box.Center().y) );
					}
				}
			}
			else // Ação de atirar
			{
				int smallest = 2000000000;
				std::vector<Minion>::iterator idxSmaller;
				for (auto it = minionArray.begin(); it != minionArray.end(); ++it)
				{
					float dist = Distance(it->box.Center(), taskQueue.front().pos);
					if ( dist < smallest )
					{
						smallest = dist;
						idxSmaller = it;
					}
				}
				idxSmaller->Shoot(taskQueue.front().pos);
				taskQueue.pop();
				shootCooldown.Restart();
				alienState = RESTING;
			}
		}
	}

	/*if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
		taskQueue.emplace( Action(Action::SHOOT, 
									InputManager::GetInstance().GetMouseX(), 
									InputManager::GetInstance().GetMouseY()) );
	if (InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON))
		taskQueue.emplace( Action(Action::MOVE, 
									InputManager::GetInstance().GetMouseX(), 
									InputManager::GetInstance().GetMouseY()) );*/


	rotation += ALIEN_ROTATION_SPEED * dt;

	// Update minions
	for (auto it = minionArray.begin(); it != minionArray.end(); ++it)
		it->Update(dt);
}



/* ************************************************************
 *
 * Render
 *
 *************************************************************/
void Alien::Render()
{
	sp.Render(box.x, box.y, rotation);

	for (auto it = minionArray.begin(); it != minionArray.end(); ++it)
		it->Render();
}


/* ************************************************************
 *
 * Checar se está morto
 *
 *************************************************************/
bool Alien::IsDead()
{
	return hp == 0 ? true : false;
}


/* ************************************************************
 *
 * Type Alien
 *
 *************************************************************/
bool Alien::Is(std::string type) const
{
	return (type == "Alien");
}


/* ************************************************************
 *
 * Colisao Alien
 *
 *************************************************************/
void Alien::NotifyCollision(const GameObject& other)
{
	if (other.Is("Bullet"))
	{
		Bullet& bullet = (Bullet&)other;
		if ( !bullet.targetsPlayer )
		{
			hp -= 10;
			if (hp <= 0)
			{
				Die();
			}
		}
	}
}


/* ************************************************************
 *
 * Morte Alien
 *
 *************************************************************/
void Alien::Die()
{
	Sprite sprite = Sprite("img/aliendeath.png", 4, 0.08);
	StillAnimation* death = new StillAnimation(box.Center().x - sprite.GetWidth() / 2, box.Center().y - sprite.GetHeight() / 2, 0, sprite, 0.32, true);
	Game::GetInstance().GetCurrentState().AddObject(death);

	for (auto it = minionArray.begin(); it != minionArray.end(); ++it)
		it->Die();
}


/* ************************************************************
 *
 * Construtor Minion
 *
 *************************************************************/
Minion::Minion(GameObject* minionCenter, float arcOffset, float scale)
{
	center = minionCenter;
	sp = Sprite("img/minion.png");
	sp.SetScaleX(scale);
	sp.SetScaleY(scale);
	arc = arcOffset;

	// Rotacionar ao redor do alien
	Point minion;
	minion.Rotate(center->box.Center(), DISTANCE_MINION_ALIEN, arc);
	rotation = arc;
	
	box = Rect( minion.x - box.w / 2, 
				minion.y - box.h / 2, 
				sp.GetWidth(), sp.GetHeight() );
}


/* ************************************************************
 *
 * Destrutor Minion
 *
 *************************************************************/
Minion::~Minion(){}


/* ************************************************************
 *
 * Update Minion
 *
 *************************************************************/
void Minion::Update(float dt)
{
	arc += MINION_SPEED * dt;
	rotation = -arc;
	Point minion;
	minion.Rotate(center->box.Center(), DISTANCE_MINION_ALIEN, arc);
	box.x = minion.x - box.w / 2;
	box.y = minion.y - box.h / 2;
}


/* ************************************************************
 *
 * Render Minion
 *
 *************************************************************/
void Minion::Render()
{
	sp.Render(box.x, box.y, rotation);
}


/* ************************************************************
 *
 * Minion só morre qdo alien morre
 *
 *************************************************************/
bool Minion::IsDead()
{
	return false;
}


/* ************************************************************
 *
 * Type Minion
 *
 *************************************************************/
bool Minion::Is(std::string type) const
{
	return (type == "Minion");
}


/* ************************************************************
 *
 * Minion só morre qdo alien morre
 *
 *************************************************************/
void Minion::Shoot(Point pos)
{
	float angle = LineInclination(box.Center(), pos);
	Bullet* bullet = new Bullet(box.Center().x, box.Center().y, angle, ALIEN_BULLET_SPEED, ALIEN_MAX_BULLET_DISTANCE, true, "img/minionBullet2.png", 3, 0.06);
	Game::GetInstance().GetCurrentState().AddObject(bullet);
}


/* ************************************************************
 *
 * Colisao Minion
 *
 *************************************************************/
void Minion::NotifyCollision(const GameObject& other){}




/* ************************************************************
 *
 * Morte Minion
 *
 *************************************************************/
void Minion::Die()
{
	Sprite sprite = Sprite("img/miniondeath.png", 4, 0.08);
	StillAnimation* death = new StillAnimation(box.Center().x - sprite.GetWidth() / 2, box.Center().y - sprite.GetHeight() / 2, 0, sprite, 0.32, true);
	Game::GetInstance().GetCurrentState().AddObject(death);
}