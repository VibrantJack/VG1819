#include <iostream>

#include "kitten\K_Game.h"
#include "kitten\K_Common.h"

#include "kitten\K_Singletons.h"
#include "puppy\P_Singletons.h"
#include "kitten\audio\AudioEngineWrapper.h"

#include "kitten\K_GameObject.h"

#include "puppy\Text\TextBox.h"

#include "kitten\Camera.h"
#include "kitten\CubeRenderable.h"
#include "kitten\QuadRenderable.h"
#include "_Project\MoveByMouseRightClickDrag.h"
#include "kitten\mouse picking\ClickableBox.h"

#include "gameworld\GameBoard.h"

#include "kibble/kibble.hpp"
#include "unit/UnitTest.h"

//board clickable
#include "board/clickable/PrintWhenClicked.h"

#include "board/BoardManager.h"

// Only for testing the event system
#include "kitten\event_system\EventExample.h"

#include "userinterface\InterfaceBuilder.h"

#define DEBUG

namespace kitten
{
	void createSingletons()
	{
		AudioEngineWrapper::createInstance();

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
		puppy::FontTable::createInstance();

		kibble::initializeKibbleRelatedComponents();

		ability::StatusManager::createInstance();
		ability::AbilityManager::createInstance();
		ability::AbilityNodeManager::createInstance();

		unit::InitiativeTracker::createInstance();

		BoardManager::createInstance();
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

		//create board
		BoardManager::getInstance()->createBoard();

		/*
		//Example of Parent / Children : REMOVE WHEN TESTING DONE OR BUGS NOT BEING FOUND
		K_GameObject* parentTest = K_GameObjectManager::getInstance()->createNewGameObject();
		parentTest->getTransform().place(-3, 0, 0);
		CubeRenderable* renderable = static_cast<CubeRenderable*>(compMan->createComponent("CubeRenderable"));
		renderable->setTexture("textures/crap/cartoon_cobble.tga");
		parentTest->addComponent(renderable);

		K_GameObject* firstChild = K_GameObjectManager::getInstance()->createNewGameObject();
		firstChild->getTransform().setIgnoreParent(false);
		firstChild->getTransform().place(3, -1, 0);
		firstChild->getTransform().setParent(&parentTest->getTransform());
		renderable = static_cast<CubeRenderable*>(compMan->createComponent("CubeRenderable"));
		PrintWhenClicked* onClick = static_cast<PrintWhenClicked*>(compMan->createComponent("PrintWhenClicked"));
		K_Component* box = compMan->createComponent("ClickableBoxBox");
		onClick->setMessage("First Child! (brick)");
		renderable->setTexture("textures/crap/cartoon_brick.tga");
		firstChild->addComponent(renderable);
		firstChild->addComponent(onClick);
		firstChild->addComponent(box);

		K_GameObject* secondChild = K_GameObjectManager::getInstance()->createNewGameObject();
		secondChild->getTransform().setIgnoreParent(false);
		secondChild->getTransform().place(-3, -2, 0);
		secondChild->getTransform().setParent(&firstChild->getTransform());
		renderable = static_cast<CubeRenderable*>(compMan->createComponent("CubeRenderable"));
		renderable->setTexture("textures/crap/cartoon_cottage.tga");
		secondChild->addComponent(renderable);

		parentTest->getTransform().scaleAbsolute(0.5f, 0.5f, 0.5f);
		secondChild->getTransform().scaleAbsolute(2.0f, 2.0f, 2.0f);

		parentTest->getTransform().rotateAbsolute(glm::vec3(0, 45, 0));
		secondChild->getTransform().rotateAbsolute(glm::vec3(0, -45, 0));
		*/

		//userinterface::InterfaceBuilder* builder = new userinterface::InterfaceBuilder();
		//builder->start();
		//delete builder;

		
		K_GameObject* gameObj = K_GameObjectManager::getInstance()->createNewGameObject();
		K_Component* fpsCalc = compMan->createComponent("FPSCalc");
		puppy::TextBox* testText = static_cast<puppy::TextBox*>(compMan->createComponent("TextBox"));
		testText->setColor(1, 1, 1);
		gameObj->addComponent(testText);
		gameObj->addComponent(fpsCalc);
		gameObj->getTransform().place2D(100, 700);

		//test unit
		unit::UnitTest::getInstanceSafe()->test();

		
		/*
		//testing ui frame and textbox
		K_GameObject* go = K_GameObjectManager::getInstance()->createNewGameObject();
		puppy::TextBox* tt = static_cast<puppy::TextBox*>(compMan->createComponent("TextBox"));
		tt->setColor(1, 1, 1);
		tt->setText("Any text");
		go->addComponent(tt);
		go->getTransform().place2D(640+640.0f*0.1,360+360.0f*0.1);

		kitten::K_GameObject* com = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		K_Component* comFrame = kitten::K_ComponentManager::getInstance()->createComponent("Frame");
		com->addComponent(comFrame);
		//com->addComponent(tt);
		com->getTransform().scale2D(0.15, 0.2);
		com->getTransform().place2D(0.1, 0.1);
		//*/

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
		puppy::FontTable::destroyInstance();
		puppy::ShaderManager::destroyAllShaders();

		ability::StatusManager::destroyInstance();
		ability::AbilityManager::destroyInstance();
		ability::AbilityNodeManager::destroyInstance();

		AudioEngineWrapper::destroyInstance();

		unit::InitiativeTracker::destroyInstance();

		BoardManager::destroyInstance();
	}

	void updateGame()
	{
		//Update sound
		AudioEngineWrapper::update();
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
		kitten::Camera* cam = K_CameraList::getInstance()->getSceneCamera();

		puppy::Renderer::getInstance()->renderAll(cam);
		puppy::StaticRenderables::getInstance()->render(cam);
	}

	// This is called every frame
	void gameCycle()
	{
		updateGame();
		renderGame();
	}

	void shutdownGame()
	{
		kitten::K_GameObjectManager::getInstance()->destroyAllGameObjects();
		destroySingletons();
	}
}