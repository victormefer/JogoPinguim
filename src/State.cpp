#include "State.h"


/* ************************************************************
 *
 * Construtor
 *
 *************************************************************/
State::State()
{
	quitRequested = false;
	popRequested = false;
}


/* ************************************************************
 *
 * Destrutor
 *
 *************************************************************/
State::~State()
{
	objectArray.clear();
}


/* ************************************************************
 *
 * Adicionar um objeto no array
 *
 *************************************************************/
void State::AddObject(GameObject* object)
{
	objectArray.emplace_back(object);
}


/* ************************************************************
 *
 * Indicar se foi pedido o encerramento
 *
 *************************************************************/
bool State::QuitRequested()
{
	return quitRequested;
}


/* ************************************************************
 *
 * Indicar se foi pedida a retirada do estado da pilha de estados do game
 *
 *************************************************************/
bool State::PopRequested()
{
	return popRequested;
}



/* ************************************************************
 *
 * Update em todos os objetos do array
 *
 *************************************************************/
void State::UpdateArray(float dt)
{
	for( int i = 0; i < objectArray.size(); ++i )
	{
		if( objectArray[i]->IsDead() )
			objectArray.erase( objectArray.begin() + i );
		else
			objectArray[i]->Update(dt);
	}
}



/* ************************************************************
 *
 * Render em todos os objetos do array
 *
 *************************************************************/
void State::RenderArray()
{
	for( int i = 0; i < objectArray.size(); ++i )
	{
		objectArray[i]->Render();
	}
}

