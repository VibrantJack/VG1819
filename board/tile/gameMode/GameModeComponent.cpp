#include "GameModeComponent.h"
#include "GameModeManager.h"
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
}

void GameModeComponent::changeTexture()
{
}
