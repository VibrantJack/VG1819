#include <iostream>

#include "kitten\K_Game.h"
#include "kitten\K_Common.h"

#include "kitten\K_Instance.h"
#include "puppy\P_Instance.h"
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
#include "kibble/databank/databank.hpp"
#include "unit/UnitTest.h"

//board clickable
#include "board/clickable/PrintWhenClicked.h"

#include "board/BoardManager.h"

#include "unitInteraction/UnitInteractionManager.h"
// Only for testing the event system
#include "kitten\event_system\EventExample.h"

#include "userinterface\InterfaceBuilder.h"

#define DEBUG

namespace kitten
{
	void createSingletons()
	{
		K_Instance::createInstance();

		puppy::P_Instance::createInstance();

		kibble::initializeKibbleRelatedComponents();

		ability::StatusManager::createInstance();
		ability::AbilityManager::createInstance();
		ability::AbilityNodeManager::createInstance();

		// Management of InitiativeTracker moved into ServerGame
		unit::InitiativeTracker::createInstance();

		BoardManager::createInstance();
    
		UnitInteractionManager::createInstance();
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

		// Deck Data importing, and exporting
		// Note that kibble assumes it's a newly generated DeckData, passing on existant DeckData would could deletion error because it's already deleted. 
		DeckData* data = new DeckData(*kibble::getDeckDataFromId(0)); // Assumes there's already atleast one deck loaded
		data->cards.push_back({ 9,2 });
		//kibble::addNewDeckData(data); // this line works, comment out or FEAR THE WRATH OF THE EVER GROWING DECK NUMBAHS INFESTING YA SAVES

		//board creator doesn't done by board manager
		//BoardManager::getInstance()->createBoard();

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

		// Networking
		//networking::ServerGame::createInstance();
		//_beginthread(serverLoop, 0, (void*)12);
		//networking::ClientGame::createInstance();
		K_GameObject* networkingMenu = K_GameObjectManager::getInstance()->createNewGameObject();
		networkingMenu->addComponent(kitten::K_ComponentManager::getInstance()->createComponent("NetworkingConsoleMenu"));

		return true;
	}

	void destroySingletons()
	{
		kibble::destroyKibbleRelatedComponents();

		K_Instance::destroyInstance();

		puppy::P_Instance::destroyInstance();

		ability::StatusManager::destroyInstance();
		ability::AbilityManager::destroyInstance();
		ability::AbilityNodeManager::destroyInstance();

		unit::InitiativeTracker::destroyInstance();

		BoardManager::destroyInstance();

		UnitInteractionManager::destroyInstance();

	}

	void updateGame()
	{
		K_Instance::update();
	}

	void renderGame()
	{
		//@TODO: Combine these? 
		puppy::P_Instance::render();
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