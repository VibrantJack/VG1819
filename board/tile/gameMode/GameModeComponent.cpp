#include "GameModeComponent.h"

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
