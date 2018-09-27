#include <iostream>

#include "kitten\K_Game.h"
#include "kitten\K_Common.h"

#include "kitten\K_Singletons.h"
#include "puppy\P_Singletons.h"

#include "kitten\K_GameObject.h"

#include "kitten\Camera.h"
#include "kitten\CubeRenderable.h"
#include "kitten\QuadRenderable.h"
#include "_Project\MoveByMouseRightClickDrag.h"
#include "_Project\PrintWhenClicked.h"
#include "kitten\mouse picking\ClickableBox.h"

#include "gameworld\GameBoard.h"

#include "kibble/kibble.hpp"

// Only for testing the event system
#include "kitten\event_system\EventExample.h"

namespace kitten
{
	void createSingletons()
	{
		input::InputManager::createInstance();
		K_CameraList::createInstance();
		K_ComponentManager::createInstance();
		K_GameObjectManager::createInstance();
		K_Time::createInstance();
		ActiveClickables::createInstance();
		EventManager::createInstance();

		puppy::MaterialManager::createInstance();
		puppy::Renderer::createInstance();
		puppy::StaticRenderables::createInstance();

		kibble::initializeKibbleRelatedComponents();
	}

	// This is called once at the beginning of the game
	bool initGame()
	{
		createSingletons();
		input::InputManager::getInstance()->resetMouse(false);

		// Temporary stuff until Kibble is ready
		K_ComponentManager* compMan = K_ComponentManager::getInstance();

		//Creating a gameobject
		//K_GameObject* camGameObj = K_GameObjectManager::getInstance()->createNewGameObject(std::string("camgameobj.txt"));
		kibble::setSceneFrom(std::string("mainscene.txt"));

		for (int x = 0; x < 15; x++)
		{
			for (int z = 0; z < 15; z++)
			{
				K_GameObject* testTile = K_GameObjectManager::getInstance()->createNewGameObject("tileobj.txt");

				PrintWhenClicked* printWhenClick = static_cast<PrintWhenClicked*>(compMan->createComponent("PrintWhenClicked"));
				printWhenClick->setMessage("grassy tile: " + std::to_string(x) + ", " + std::to_string(z));
				testTile->addComponent(printWhenClick);

				K_Component* clickBox = compMan->createComponent("ClickableBox");
				testTile->addComponent(clickBox);

				K_Component* destroyWhenClick = compMan->createComponent("DestroyOnClick");
				testTile->addComponent(destroyWhenClick);

				//K_Component* tileRenderComponent = compMan->createComponent("StaticQuadRenderable");
				//QuadRenderable* cubeRend = static_cast<QuadRenderable*>(tileRenderComponent);
				//testtile->addComponent(cubeRend);
				//cubeRend->setTexture("textures/tiles/Grassland.tga");

				testTile->getTransform().move(x, -1, z);
			}
		}
		// Testing Events
		Event* e = new Event(Event::Test_Event);
		e->putString("key", "Testing Event Trigger");

		EventExample ee;
		ee.registerListener();
		EventManager::getInstance()->triggerEvent(Event::Test_Event, e);
		//ee.deregisterListener();

		e = new Event(Event::Test_Event);
		e->putString("key", "Testing Event queue");
		EventManager::getInstance()->queueEvent(Event::Test_Event, e);

		// End testing events
		return true;
	}

	void destroySingletons()
	{
		kibble::destroyKibbleRelatedComponents();

		input::InputManager::destroyInstance();
		K_CameraList::destroyInstance();
		K_ComponentManager::destroyInstance();
		K_GameObjectManager::destroyInstance();
		K_Time::destroyInstance();
		ActiveClickables::destroyInstance();
		EventManager::destroyInstance();

		puppy::MaterialManager::destroyInstance();
		puppy::Renderer::destroyInstance();
		puppy::StaticRenderables::destroyInstance();
	}

	void updateGame()
	{
		//Update delta time
		K_Time::getInstance()->updateTime();
		//Update input
		input::InputManager::getInstance()->update();
		//Update event manager
		EventManager::getInstance()->update();

		//Update components
		K_ComponentManager::getInstance()->updateComponents();
		K_GameObjectManager::getInstance()->deleteQueuedObjects();
	}


	void renderGame()
	{
		//@TODO: Combine these? 
		const glm::mat4& sceneViewProj = K_CameraList::getInstance()->getSceneCamera()->getViewProj();
		puppy::Renderer::getInstance()->renderAll(sceneViewProj);

		puppy::StaticRenderables::getInstance()->render(sceneViewProj);
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