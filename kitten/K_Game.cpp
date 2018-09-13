#include "kitten\K_Game.h"
#include "kitten\K_Common.h"

#include "kitten\K_Singletons.h"
#include "puppy\P_Singletons.h"

#include "kitten\K_GameObject.h"

#include "kitten\Camera.h"
#include "kitten\CubeRenderable.h"

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

		//Creating a gameobject
		K_GameObject* camGameObj = K_GameObjectManager::getInstance()->createNewGameObject();
		//Creating a component, again, temporary until Kibble is ready. Don't need to static_cast, see below for quick -- shown in case need setup.
		Camera* camComp = static_cast<Camera*>(K_ComponentManager::getInstance()->createComponent("Camera"));
		camGameObj->addComponent(camComp);


		K_GameObject* cubeGameObj = K_GameObjectManager::getInstance()->createNewGameObject();
		K_Component* cubeRend = K_ComponentManager::getInstance()->createComponent("CubeRenderable");
		cubeGameObj->addComponent(cubeRend);

		cubeGameObj->getTransform().move(0, -2, 10);
		cubeGameObj->getTransform().scaleAbsolute(3, 0.5f, 3);

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