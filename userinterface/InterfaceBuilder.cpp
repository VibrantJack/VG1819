#include "InterfaceBuilder.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_ComponentManager.h"

namespace userinterface
{
	InterfaceBuilder::InterfaceBuilder()
	{

	}

	InterfaceBuilder::~InterfaceBuilder()
	{

	}

	bool InterfaceBuilder::hasUpdate() const
	{
		return true;
	}

	void InterfaceBuilder::update()
	{

	}

	void InterfaceBuilder::start()
	{
		//testing UI
		
		kitten::K_GameObject* comPortrait = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		K_Component* comFrame = kitten::K_ComponentManager::getInstance()->createComponent("Frame");
		comPortrait->addComponent(comFrame);
		comPortrait->getTransform().scale2D(0.3, 0.4);
		comPortrait->getTransform().place2D(-0.90, 0.55);
		
		kitten::K_GameObject* hand = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		K_Component* handFrame = kitten::K_ComponentManager::getInstance()->createComponent("Frame");
		hand->addComponent(handFrame);
		hand->getTransform().scale2D(1.0, 0.4);
		hand->getTransform().place2D(-.90, -0.90);

		kitten::K_GameObject* deck = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		K_Component* deckFrame = kitten::K_ComponentManager::getInstance()->createComponent("Frame");
		deck->addComponent(deckFrame);
		deck->getTransform().scale2D(0.3, 0.4);
		deck->getTransform().place2D(0.65, -0.90);
	}
}