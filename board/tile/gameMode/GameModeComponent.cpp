#include "GameModeComponent.h"
#include "GameModeManager.h"
#include "kitten/K_GameObjectManager.h"

GameModeComponent::GameModeComponent()
{
}

GameModeComponent::~GameModeComponent()
{
}

void GameModeComponent::addTile(TileInfo * p_info)
{
	m_tileList.push_back(p_info);
}

void GameModeComponent::init()
{
	//remove this component if no tile to check
	if (m_tileList.size() == 0)
		GameModeManager::getInstance()->removeModeComponent(this);
	else if( m_filePath.length() > 0)//have file path
	{
		for (auto tile : m_tileList)
		{
			changeTileDisplay(tile);
		}
	}

}

void GameModeComponent::changeTileDisplay(TileInfo* p_info)
{
	std::vector<kitten::K_GameObject*> list;

	kitten::K_GameObject* go = kitten::K_GameObjectManager::getInstance()->createNewGameObject(m_filePath);

	list.push_back(go);

	p_info->changeDecoration(list);
}
