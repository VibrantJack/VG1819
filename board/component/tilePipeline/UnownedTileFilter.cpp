#include "TileFliter.h"

void UnownedTileFilter::filter(kitten::Event::TileList * p_list)
{
	if (!m_enabled)
		return;

	//remove tiles that's not owned
	auto it = p_list->begin();
	while (it != p_list->end())
	{
		kitten::K_GameObject* tileGO = BoardManager::getInstance()->getTile(it->first, it->second);
		int owner = tileGO->getComponent<TileInfo>()->getOwnerId();
		if (owner != m_pipe->m_source->m_clientId)
		{
			it = p_list->erase(it);
		}
		else
		{
			it++;
		}
	}
}