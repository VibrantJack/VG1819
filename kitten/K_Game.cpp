#include <iostream>

#include "kitten\K_Game.h"
#include "kitten\K_Common.h"

#include "kitten\K_Singletons.h"
#include "puppy\P_Singletons.h"

#include "kitten\K_GameObject.h"

#include "kitten\Camera.h"
#include "kitten\CubeRenderable.h"
#include "_Project\MoveByMouseRightClickDrag.h"
#include "_Project\PrintWhenClicked.h"

#include "gameworld\GameBoard.h"

#include "kibble/kibble.hpp"

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

		puppy::MaterialManager::createInstance();
		puppy::Renderer::createInstance();

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
				K_GameObject* testtile = K_GameObjectManager::getInstance()->createNewGameObject();
				K_Component* grassTileInfo = compMan->createComponent("Grassland");
				PrintWhenClicked* clickableComp = static_cast<PrintWhenClicked*>(compMan->createComponent("PrintWhenClicked"));
				clickableComp->setMessage("grassy tile");
				testtile->addComponent(grassTileInfo);
				testtile->addComponent(clickableComp);
				K_Component* tileRenderComponent = compMan->createComponent("CubeRenderable");
				CubeRenderable* cubeRend = static_cast<CubeRenderable*>(tileRenderComponent);
				testtile->addComponent(cubeRend);
				cubeRend->setTexture("textures/tiles/Grassland.tga");

				testtile->getTransform().move(x, -1, z);
			}
		}

	

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

		puppy::MaterialManager::destroyInstance();
		puppy::Renderer::destroyInstance();
	}

	void updateGame()
	{
		//Update delta time
		K_Time::getInstance()->updateTime();
		//Update input
		input::InputManager::getInstance()->update();

		//Update components
		K_ComponentManager::getInstance()->updateComponents();
	}


	void renderGame()
	{
		//@TODO: Combine these? 
		const glm::mat4& sceneViewProj = K_CameraList::getInstance()->getSceneCamera()->getViewProj();
		puppy::Renderer::getInstance()->renderAll(sceneViewProj);
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