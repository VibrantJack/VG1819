#include "kitten\K_Game.h"

namespace kitten
{
	// This is called once at the beginning of the game
	bool initGame()
	{
		return true;
	}

	// This is called every frame
	void gameCycle()
	{
		updateGame();
		renderGame();
	}

	void updateGame()
	{
		//Update delta time

		//Update gameobjects
	}

	void renderGame()
	{
		
	}

	void shutdownGame()
	{

	}
}