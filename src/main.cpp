#include "Game.h"
#include "TitleState.h"
#include <exception>

int main (int argc, char** argv)
{
	Game* game = new Game ("Victor Ferreira - 10/0126588", 1024, 600);
	try
	{
		TitleState* title = new TitleState();
		game->Push(title);
		game->Run();
	}
	catch (std::exception& ex)
	{
		std::cout << "Excecao nao tratada: " << ex.what() << std::endl;
	}
	delete game;
	return 0;
}