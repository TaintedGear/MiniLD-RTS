#include "SDL.h"
#include "Game.h"

int main(int argc, char* args[])
{
	Game game;

	game.Initalise();
	game.Run();
	game.Shutdown();

	return -1;
}