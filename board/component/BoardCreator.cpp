// BoardCreator
//
// Originally only created the tile objects that make up the board @Callum
// Multipurposed to handle highlighting and unhighlighting of tiles @Ken
// *Should rename component to something that better represents this.
// TODO: Either verify tiles to be highlighted are valid here or ensure it is
//	done before the tile list is sent here. E.g. A commander cannot highlight
//	tiles owned by the other commander

#include "BoardCreator.h"
#include "kitten/K_Component.h"
#include "kitten/K_GameObjectManager.h"
#include "kitten/K_ComponentManager.h"

#include "kitten/QuadRenderable.h"
#include "_Project/UseAbilityWhenClicked.h"
//clickable
#include "board/clickable/ManipulateTileOnClick.h"
#include "board/clickable/PrintWhenClicked.h"
#include "board/clickable/SendSelfOnClick.h"
//tile
#include "board/tile/TileInfo.h"

#include "board/BoardManager.h"

BoardCreator::BoardCreator()
{
}

BoardCreator::~BoardCreator()
{
}

kitten::K_GameObject * BoardCreator::createTile(int x, int z)
{
	// Initializing Tiles on board
	kitten::K_GameObjectManager* gameObjMan = kitten::K_GameObjectManager::getInstance();
	kitten::K_ComponentManager* compMan = kitten::K_ComponentManager::getInstance();

	kitten::K_GameObject* tileGO = gameObjMan->createNewGameObject("tileobj.txt");

	PrintWhenClicked* printWhenClick = static_cast<PrintWhenClicked*>(compMan->createComponent("PrintWhenClicked"));
	printWhenClick->setMessage("grassy tile: " + std::to_string(x) + ", " + std::to_string(z));
	tileGO->addComponent(printWhenClick);

	ManipulateTileOnClick* manipTileOnClick = static_cast<ManipulateTileOnClick*>(compMan->createComponent("ManipulateTileOnClick"));
	tileGO->addComponent(manipTileOnClick);

	SendSelfOnClick* sendSelfOnClick = static_cast<SendSelfOnClick*>(compMan->createComponent("SendSelfOnClick"));
	tileGO->addComponent(sendSelfOnClick);

	kitten::K_Component* tileInfo = new TileInfo(x, z);
	tileGO->addComponent(tileInfo);

	kitten::K_Component* clickBox = compMan->createComponent("ClickableBox");
	tileGO->addComponent(clickBox);

	kitten::Transform& transform = tileGO->getTransform();
	transform.move(x, -1, z);


	return tileGO;
}

kitten::K_GameObject * BoardCreator::getTile(int x, int z)
{
	std::vector<kitten::K_GameObject *> tileList = BoardManager::getInstance()->m_tileList;
	std::pair<int, int> pos (x,z);
	int x_length = BoardManager::getInstance()->m_dimension.first;

	if (pos == tileList[x * x_length + z]->getComponent<TileInfo>()->getPos())
	{
		return tileList[x * x_length + z];
	}

	assert(false);//not found tile
	return nullptr;
}
