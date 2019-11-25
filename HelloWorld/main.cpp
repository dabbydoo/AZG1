#include "Game.h"
#include <Windows.h>
#include <mmsystem.h>

#undef main
int main()
{
	

	//system("pause");

	//Create the Game
	Game game;

	//Initialize the game
	game.InitGame();

	
	PlaySound(TEXT("SoundTrack.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	//Runs the game until it returns :)
	return game.Run();

	

	
}