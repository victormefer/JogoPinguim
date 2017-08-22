#include "InputManager.h"



/* ************************************************************
 *
 * Retornar instancia unica
 *
 *************************************************************/
InputManager& InputManager::GetInstance()
{
	static InputManager instance;
	return instance;
}


/* ************************************************************
 *
 * Construtor
 *
 *************************************************************/
InputManager::InputManager()
{
	for (int i = 0; i < 6; i++)
	{
		mouseState[i] = false;
		mouseUpdate[i] = 0;
	}

	for (int i = 0; i < 416; i++)
	{
		keyState[i] = false;
		keyUpdate[i] = 0;
	}

	quitRequested = false;
	updateCounter = 0;
	mouseX = 0;
	mouseY = 0;
}


/* ************************************************************
 *
 * Pegar eventos de inputs
 *
 *************************************************************/
void InputManager::Update()
{
	SDL_Event event;

	updateCounter++;
	quitRequested = false;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			quitRequested = true;
		}

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			mouseState[event.button.button] = true;
			mouseUpdate[event.button.button] = updateCounter;
		}

		if (event.type == SDL_MOUSEBUTTONUP)
		{
			mouseState[event.button.button] = false;
			mouseUpdate[event.button.button] = updateCounter;
		}

		if (event.type == SDL_KEYDOWN && !event.key.repeat)
		{
			if (event.key.keysym.sym < 0x40000000)
			{
				keyState[event.key.keysym.sym] = true;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
			else
			{
				keyState[event.key.keysym.sym - 0x3FFFFF81] = true;
				keyUpdate[event.key.keysym.sym - 0x3FFFFF81] = updateCounter;
			}
		}

		if (event.type == SDL_KEYUP && !event.key.repeat)
		{
			if (event.key.keysym.sym < 0x40000000)
			{
				keyState[event.key.keysym.sym] = false;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
			else
			{
				keyState[event.key.keysym.sym - 0x3FFFFF81] = false;
				keyUpdate[event.key.keysym.sym - 0x3FFFFF81] = updateCounter;
			}
		}
	}
}


/* ************************************************************
 *
 * True se tecla foi pressionada neste frame
 *
 *************************************************************/
bool InputManager::KeyPress(int key)
{
	int i = key;
	if (key >= 0x40000000)
		i -= 0x3FFFFF81;

	if ( keyState[i] && keyUpdate[i] == updateCounter )
		return true;
	else
		return false;
}


/* ************************************************************
 *
 * True se tecla foi solta neste frame
 *
 *************************************************************/
bool InputManager::KeyRelease(int key)
{
	int i = key;
	if (key >= 0x40000000)
		i -= 0x3FFFFF81;

	if ( !keyState[i] && keyUpdate[i] == updateCounter )
		return true;
	else
		return false;
}


/* ************************************************************
 *
 * True se tecla está sendo pressionada
 *
 *************************************************************/
bool InputManager::IsKeyDown(int key)
{
	int i = key;
	if (key >= 0x40000000)
		i -= 0x3FFFFF81;

	if (keyState[i])
		return true;
	else
		return false;
}


/* ************************************************************
 *
 * True se mouse foi pressionada neste frame
 *
 *************************************************************/
bool InputManager::MousePress(int button)
{
	if ( mouseState[button] && mouseUpdate[button] == updateCounter )
		return true;
	else
		return false;
}


/* ************************************************************
 *
 * True se mouse foi solta neste frame
 *
 *************************************************************/
bool InputManager::MouseRelease(int button)
{
	if ( !mouseState[button] && mouseUpdate[button] == updateCounter )
		return true;
	else
		return false;
}


/* ************************************************************
 *
 * True se mouse está sendo pressionado
 *
 *************************************************************/
bool InputManager::IsMouseDown(int button)
{
	if (mouseState[button])
		return true;
	else
		return false;
}


/* ************************************************************
 *
 * Coordenada X do mouse
 *
 *************************************************************/
int InputManager::GetMouseX()
{
	return mouseX + Camera::pos.x;
}


/* ************************************************************
 *
 * Coordenada Y do mouse
 *
 *************************************************************/
int InputManager::GetMouseY()
{
	return mouseY + Camera::pos.y;
}


/* ************************************************************
 *
 * True se foi pedido o fechamento
 *
 *************************************************************/
bool InputManager::QuitRequested()
{
	return quitRequested;
}