#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <memory>
#include "Resources.h"
#include "InputManager.h"

class State;

class Game
{
public:
	// Construtor e destrutor
	Game(const char* title, int width, int height);
	~Game();

	void Run();

	void Push(State* state);

	static Game& GetInstance();
	SDL_Renderer* GetRenderer();

	State& GetCurrentState();

	float GetDeltaTime();

private:
	void CalculateDeltaTime();

	int frameStart;
	float dt;

	static Game* instance;

	SDL_Window* window;
	SDL_Renderer* renderer;
	std::stack<std::unique_ptr<State>> stateStack;
	State* storedState;
};

#include "State.h"


#endif // GAME_H