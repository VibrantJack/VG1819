#include "kitten\K_Game.h"
#include "kitten\K_Common.h"
#include "kitten\K_ComponentManager.h"

namespace kitten
{
	void createSingletons()
	{
		K_Time::createInstance();
		K_ComponentManager::createInstance();
	}

	// This is called once at the beginning of the game
	bool initGame()
	{
		createSingletons();

		return true;
	}

	void destroySingletons()
	{
		K_Time::destroyInstance();
		K_ComponentManager::destroyInstance();
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

	// This is called every frame
	void gameCycle()
	{
		updateGame();
		renderGame();
	}

	void shutdownGame()
	{
		destroySingletons();
	}
}