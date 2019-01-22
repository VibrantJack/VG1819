#include "TileFliter.h"

void NotDPFilter::filter(kitten::Event::TileList * p_list)
{
	if (!m_enabled)
		return;

	//remove tiles that isn't demonic presence
	auto it = p_list->begin();
	while (it != p_list->end())
	{
		kitten::K_GameObject* tileGO = BoardManager::getInstance()->getTile(it->first, it->second);

		if (!tileGO->getComponent<TileInfo>()->isDemonicPresence())
		{
			it = p_list->erase(it);
			continue;
		}
		else
			it++;
	}
}