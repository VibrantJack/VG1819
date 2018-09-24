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

#include "gameworld\GameBoard.h"

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
		puppy::StaticRenderables::createInstance();
	}

	// This is called once at the beginning of the game
	bool initGame()
	{
		createSingletons();
		input::InputManager::getInstance()->resetMouse(false);

		// Temporary stuff until Kibble is ready
		K_ComponentManager* compMan = K_ComponentManager::getInstance();


		//Creating a gameobject
		K_GameObject* camGameObj = K_GameObjectManager::getInstance()->createNewGameObject();
		K_Component* camComp = compMan->createComponent("Camera");
		K_Component* mouseMove = compMan->createComponent("MoveByMouseRightClickDrag");
		K_Component* zoomComp = compMan->createComponent("ZoomByMouseWheel");
		camGameObj->getTransform().move(7.0f, 5.0f, -5.0f);
		camGameObj->getTransform().rotateAbsolute(glm::vec3(-33, 0, 0));
		camGameObj->addComponent(zoomComp);
		camGameObj->addComponent(camComp);
		camGameObj->addComponent(mouseMove);


		for (int x = 0; x < 15; x++)
		{
			for (int z = 0; z < 15; z++)
			{
				K_GameObject* testtile = K_GameObjectManager::getInstance()->createNewGameObject();
				K_Component* grassTileInfo = compMan->createComponent("Grassland");
				PrintWhenClicked* clickableComp = static_cast<PrintWhenClicked*>(compMan->createComponent("PrintWhenClickedQuad"));
				clickableComp->setMessage("grassy tile: " + std::to_string(x) + ", " + std::to_string(z));
				testtile->addComponent(grassTileInfo);
				testtile->addComponent(clickableComp);
				K_Component* tileRenderComponent = compMan->createComponent("StaticQuadRenderable");
				QuadRenderable* cubeRend = static_cast<QuadRenderable*>(tileRenderComponent);
				testtile->addComponent(cubeRend);
				cubeRend->setTexture("textures/tiles/Grassland.tga");
				testtile->getTransform().move(x, -1, z);
			}
		}

		return true;
	}

	void destroySingletons()
	{
		input::InputManager::destroyInstance();
		K_CameraList::destroyInstance();
		K_ComponentManager::destroyInstance();
		K_GameObjectManager::destroyInstance();
		K_Time::destroyInstance();
		ActiveClickables::destroyInstance();

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

		//Update components
		K_ComponentManager::getInstance()->updateComponents();
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