#include "BoardCreator.h"
#include "PrintWhenClicked.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_ComponentManager.h"

#include "TileInfo.h"
#include "kitten\QuadRenderable.h"
#include "UseAbilityWhenClicked.h"

kitten::K_GameObject* BoardCreator::m_pTileList[15][15];

BoardCreator::BoardCreator()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Highlight_Tile,
		this,
		std::bind(&BoardCreator::highlightTile, this, std::placeholders::_1, std::placeholders::_2));

	//m_pTileList.resize(15);
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
			m_pTileList[x][z] = testTile;

			PrintWhenClicked* printWhenClick = static_cast<PrintWhenClicked*>(compMan->createComponent("PrintWhenClicked"));
			printWhenClick->setMessage("grassy tile: " + std::to_string(x) + ", " + std::to_string(z));
			testTile->addComponent(printWhenClick);

			K_Component* clickBox = compMan->createComponent("ClickableBox");
			testTile->addComponent(clickBox);			

			// Error when Tile QuadRenderable component is not static and is destroyed on click
			//K_Component* destroyWhenClick = compMan->createComponent("DestroyOnClick");
			//testTile->addComponent(destroyWhenClick);

			K_Component* tileInfo = new TileInfo(x, z);
			testTile->addComponent(tileInfo);

			kitten::Transform& transform = testTile->getTransform();
			transform.setParent(&m_attachedObject->getTransform());
			transform.setIgnoreParent(false);
			transform.move(x, -1, z);
		}
	}

	compMan->destroyComponent(this);
}

void BoardCreator::highlightTile(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	/*int x = p_data->getInt(TILE_POS_X);
	int y = p_data->getInt(TILE_POS_Y);

	kitten::K_GameObject* tile = m_pTileList[x][y];

	kitten::QuadRenderable* quad = tile->getComponent<kitten::QuadRenderable>();
	quad->setColorTint(glm::vec4(0.0f, 0.0f, 0.5f, 1.0f));

	TileInfo* tileInfo = tile->getComponent<TileInfo>();
	tileInfo->setHighlighted(true);*/


	kitten::K_GameObject* tile;

	auto it = p_data->getTileList()->cbegin();
	for (; it != p_data->getTileList()->cend(); ++it)
	{
		tile = m_pTileList[it->first][it->second];

		kitten::QuadRenderable* quad = tile->getComponent<kitten::QuadRenderable>();
		quad->setColorTint(glm::vec4(0.0f, 0.0f, 0.5f, 1.0f));

		TileInfo* tileInfo = tile->getComponent<TileInfo>();
		tileInfo->setHighlighted(true);
	}
}

void BoardCreator::unhighlightTile(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	int x = p_data->getInt(TILE_POS_X);
	int y = p_data->getInt(TILE_POS_Y);

	kitten::K_GameObject* tile = m_pTileList[x][y];

	kitten::QuadRenderable* quad = tile->getComponent<kitten::QuadRenderable>();
	quad->setColorTint(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	TileInfo* tileInfo = tile->getComponent<TileInfo>();
	tileInfo->setHighlighted(false);
}