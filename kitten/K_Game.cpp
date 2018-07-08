#include "kitten\K_Game.h"
#include "kitten\K_Common.h"
namespace kitten
{
	// This is called once at the beginning of the game
	bool initGame()
	{
		createSingletons();

		return true;
	}

	void createSingletons()
	{
		K_Time::createInstance();
		K_ComponentManager::createInstance();
	}

	void destroySingletons()
	{
		K_Time::destroyInstance();
		K_ComponentManager::destroyInstance();
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
		K_Time::getInstance()->updateTime();

		//Update components
		K_ComponentManager::getInstance()->updateComponents();
	}

	void renderGame()
	{
		
	}

	void shutdownGame()
	{
		destroySingletons();
	}
}