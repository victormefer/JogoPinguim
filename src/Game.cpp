#include "Game.h"

// Variável estática de instancia
Game* Game::instance;


/* ************************************************************
 *
 * Construtor
 *
 *************************************************************/
Game::Game(const char* title, int width, int height)
{
	dt = 0.0;
	frameStart = 0;
	srand(time(NULL));

	// Checar se ha somente uma instancia de Game
	if (this->instance != NULL)
	{
		std::cerr << "Ja existe uma instancia do jogo executando" << std::endl;
		exit(1);
	}
	instance = this;

	// Inicializações da SDL
	if ( SDL_Init ( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER ) != 0 )
	{
		std::cerr << "Erro na inicializacao da SDL" << std::endl << SDL_GetError() << std::endl;
		exit(1);
	}

	int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	int initted = IMG_Init (flags);
	if ( initted&flags != flags )
	{
		std::cerr << "Erro na inicializacao da SDL_image" << std::endl << IMG_GetError() << std::endl;
		exit(1);
	}

	flags = MIX_INIT_OGG;
	initted = Mix_Init(flags);
	if ( initted&flags != flags )
	{
		std::cerr << "Erro na inicializacao da SDL_mixer" << std::endl << Mix_GetError() << std::endl;
		exit(1);
	}

	if ( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0 )
	{
		std::cerr << "Erro na inicializacao da SDL_mixer" << std::endl << Mix_GetError() << std::endl;
		exit(1);
	}

	if ( TTF_Init() != 0 )
	{
		std::cerr << "Erro na inicializacao da SDL_ttf" << std::endl << TTF_GetError() << std::endl;
		exit(1);
	}

	// Pegar resolucao da tela
	// SDL_DisplayMode mode;
	// if (SDL_GetDesktopDisplayMode(0, &mode) != 0) {
	// 	std::cerr << "Erro na criacao da janela do jogo" << 
	// 		std::endl << SDL_GetError() << std::endl;
	// 	exit(1);
	// }

	window = SDL_CreateWindow ( title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, /*mode.w*/width, /*mode.h*/height, 0 );
	if (window == NULL)
	{
		std::cerr << "Erro na criacao da janela do jogo" << std::endl << SDL_GetError() << std::endl;
		exit(1);
	}

	// Setar fullscreen
	// if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) != 0) {
	// 	std::cerr << "Erro na criacao da janela do jogo" << 
	// 		std::endl << SDL_GetError() << std::endl;
	// 	exit(1);
	// }
	// SDL_MaximizeWindow(window);

	renderer = SDL_CreateRenderer ( window, -1, SDL_RENDERER_ACCELERATED );
	if (renderer == NULL)
	{
		std::cerr << "Erro na criacao do renderizador do jogo" << std::endl << SDL_GetError() << std::endl;
		exit(1);
	}

	// Inicializar State
	storedState = NULL;

}


/* ************************************************************
 *
 * Destrutor
 *
 *************************************************************/
Game::~Game()
{
	if (storedState != NULL)
		delete(storedState);
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


/* ************************************************************
 *
 *************************************************************/
Game& Game::GetInstance()
{
	return *instance;
}


/* ************************************************************
 *
 *************************************************************/
State& Game::GetCurrentState()
{
	return *stateStack.top();
}


/* ************************************************************
 *
 *************************************************************/
SDL_Renderer* Game::GetRenderer()
{
	return renderer;
}


/* ************************************************************
 *
 * Guarda referencia a estado que sera empilhado na Run
 *
 *************************************************************/
void Game::Push(State* state)
{
	storedState = state;
}


/* ************************************************************
 *
 * Função principal do Game Loop
 *
 *************************************************************/
void Game::Run()
{
	if (storedState != NULL)
	{
		stateStack.emplace(storedState);
		storedState = NULL;
	}

	// Main game loop
	while (!stateStack.empty() && !stateStack.top()->QuitRequested())
	{
		CalculateDeltaTime();

		InputManager::GetInstance().Update();

		stateStack.top()->Update(dt);
		stateStack.top()->Render();
		SDL_RenderPresent(renderer);

		if (stateStack.top()->PopRequested())
		{
			stateStack.pop();
			// Destruir todos os recursos carregados
			Resources::ClearImages();
			Resources::ClearMusic();
			Resources::ClearSound();
			Resources::ClearFonts();
			stateStack.top()->Resume();
		}

		if (storedState != NULL)
		{
			stateStack.top()->Pause();
			stateStack.emplace(storedState);
			storedState = NULL;
		}

		//SDL_Delay(33);
		if ( (float)(SDL_GetTicks() - frameStart) < 1000.0 / 60.0 )
			SDL_Delay( (1000.0/60.0) - (frameStart - SDL_GetTicks()) );
	}

	// Remover todos os states da pilha
	if (stateStack.top()->QuitRequested())
	{
		while(!stateStack.empty())
			stateStack.pop();

		// Destruir todos os recursos carregados
		Resources::ClearImages();
		Resources::ClearMusic();
		Resources::ClearSound();
		Resources::ClearFonts();
	}
}


/* ************************************************************
 *
 * Calcula o tempo entre o frame anterior e o atual
 *
 *************************************************************/
void Game::CalculateDeltaTime()
{
	dt = (float)(SDL_GetTicks() - frameStart) / 1000.0;
	frameStart = SDL_GetTicks();
	//std::cout << dt << std::endl;
}


/* ************************************************************
 *
 *************************************************************/
float Game::GetDeltaTime()
{
	return dt;
}