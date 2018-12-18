#include "TileFliter.h"

void OwnedTileFilter::filter(kitten::Event::TileList * p_list)
{
	if (!m_enabled)
		return;

	//remove tiles that has owner
	auto it = p_list->begin();
	while (it != p_list->end())
	{
		kitten::K_GameObject* tileGO = BoardManager::getInstance()->getTile(it->first, it->second);
		int owner = tileGO->getComponent<TileInfo>()->getOwnerId();
		if (owner != -1)
		{
			it = p_list->erase(it);
		}
		else
		{
			it++;
		}
	}
}