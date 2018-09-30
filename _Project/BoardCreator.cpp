#include "BoardCreator.h"
#include "kitten\K_GameObject.h"
#include "PrintWhenClicked.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_ComponentManager.h"

BoardCreator::BoardCreator()
{

}

BoardCreator::~BoardCreator()
{

}

void BoardCreator::start()
{
	kitten::K_GameObjectManager* gameObjMan = kitten::K_GameObjectManager::getInstance();
	kitten::K_ComponentManager* compMan = kitten::K_ComponentManager::getInstance();

	for (int x = 0; x < 15; x++)
	{
		for (int z = 0; z < 15; z++)
		{
			kitten::K_GameObject* testTile = gameObjMan->createNewGameObject("tileobj.txt");

			PrintWhenClicked* printWhenClick = static_cast<PrintWhenClicked*>(compMan->createComponent("PrintWhenClicked"));
			printWhenClick->setMessage("grassy tile: " + std::to_string(x) + ", " + std::to_string(z));
			testTile->addComponent(printWhenClick);

			K_Component* clickBox = compMan->createComponent("ClickableBox");
			testTile->addComponent(clickBox);

			K_Component* destroyWhenClick = compMan->createComponent("DestroyOnClick");
			testTile->addComponent(destroyWhenClick);

			kitten::Transform& transform = testTile->getTransform();
			transform.setParent(&m_attachedObject->getTransform());
			transform.setIgnoreParent(false);
			transform.move(x, -1, z);
		}
	}

	compMan->destroyComponent(this);
}