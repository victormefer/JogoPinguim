#include "StageState.h"


/* ************************************************************
 *
 * Construtor
 *
 *************************************************************/
StageState::StageState() : bg("img/ocean.jpg")
{
	tileSet = new TileSet(64, 64, "img/tileset.png");
	tileMap = new TileMap("map/tileMap.txt", tileSet);
	penguins = new Penguins(512, 300);
	objectArray.emplace_back(penguins);
	alien[0] = new Alien(200, 600, 6);
	objectArray.emplace_back(alien[0]);
	alien[1] = new Alien(700, 550, 6);
	objectArray.emplace_back(alien[1]);
	alien[2] = new Alien(900, 1000, 6);
	objectArray.emplace_back(alien[2]);
	Camera::Follow(penguins);
}


/* ************************************************************
 *
 * Destrutor
 *
 *************************************************************/
/*StageState::~StageState()
{
	objectArray.clear();
}*/


/* ************************************************************
 *
 * Atualizar estado
 *
 *************************************************************/
void StageState::Update(float dt)
{
	// GAME OVER
	if (Penguins::player == NULL)
	{
		Camera::Unfollow();
	}

	if ( InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY) )
		quitRequested = true;

	Camera::Update(dt);

	UpdateArray(dt);

	// Checar colisão
	for( int i = 0; i < objectArray.size(); ++i )
	{
		for ( int j = i + 1; j < objectArray.size(); ++j )
		{
			if ( Collision::IsColliding(objectArray[i]->box, objectArray[j]->box, objectArray[i]->rotation, objectArray[j]->rotation) )
			{
				objectArray[i]->NotifyCollision(*objectArray[j]);
				objectArray[j]->NotifyCollision(*objectArray[i]);
			}
		}
	}
}


/* ************************************************************
 *
 * Renderizar tela
 *
 *************************************************************/
void StageState::Render()
{
	bg.Render(Camera::pos.x, Camera::pos.y);

	tileMap->RenderLayer(0, Camera::pos.x, Camera::pos.y);

	RenderArray();

	tileMap->RenderLayer(1, Camera::pos.x, Camera::pos.y);
}



/* ************************************************************
 *
 * Pausar estado quando não estiver no topo da pilha
 *
 *************************************************************/
void StageState::Pause()
{

}



/* ************************************************************
 *
 * Resumir estado quando voltar pro topo da pilha
 *
 *************************************************************/
void StageState::Resume()
{
	
}