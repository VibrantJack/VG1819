#include <iostream>

#include "kitten\K_Game.h"
#include "kitten\K_Common.h"

#include "kitten\K_Singletons.h"
#include "puppy\P_Singletons.h"

#include "kitten\K_GameObject.h"

#include "kitten\Camera.h"
#include "kitten\CubeRenderable.h"
#include "_Project\MoveByMouseRightClickDrag.h"

namespace kitten
{
	void createSingletons()
	{
		input::InputManager::createInstance();
		K_CameraList::createInstance();
		K_ComponentManager::createInstance();
		K_GameObjectManager::createInstance();
		K_Time::createInstance();

		puppy::MaterialManager::createInstance();
		puppy::Renderer::createInstance();
	}

	// This is called once at the beginning of the game
	bool initGame()
	{
		createSingletons();

		// Temporary stuff until Kibble is ready
		K_ComponentManager* compMan = K_ComponentManager::getInstance();
		input::InputManager::getInstance()->resetMouse(false);


		//Creating a gameobject
		K_GameObject* camGameObj = K_GameObjectManager::getInstance()->createNewGameObject();
		K_Component* camComp = compMan->createComponent("Camera");
		K_Component* mouseMove = compMan->createComponent("MoveByMouseRightClickDrag");
		K_Component* zChange = compMan->createComponent("ZoomByMouseWheel");
		camGameObj->addComponent(camComp);
		camGameObj->addComponent(mouseMove);
		camGameObj->addComponent(zChange);
		camGameObj->getTransform().rotateRelative(glm::vec3(-33.0f, 0, 0));


		K_GameObject* cubeGameObj = K_GameObjectManager::getInstance()->createNewGameObject();
		K_Component* cubeRend = compMan->createComponent("CubeRenderable");
		cubeGameObj->addComponent(cubeRend);

		cubeGameObj->getTransform().move(0, -10, 30);
		cubeGameObj->getTransform().scaleAbsolute(30, 0.5f, 30);

		return true;
	}

	void destroySingletons()
	{
		input::InputManager::destroyInstance();
		K_CameraList::destroyInstance();
		K_ComponentManager::destroyInstance();
		K_GameObjectManager::destroyInstance();
		K_Time::destroyInstance();
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