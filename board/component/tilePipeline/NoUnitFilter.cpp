#include "TileFliter.h"

void NoUnitFilter::filter(kitten::Event::TileList * p_list)
{
	if (!m_enabled)
		return;

	//remove tiles that doesn't have unit
	auto it = p_list->begin();
	while (it != p_list->end())
	{
		kitten::K_GameObject* tileGO = BoardManager::getInstance()->getTile(it->first, it->second);
		if (!tileGO->getComponent<TileInfo>()->hasUnit())
		{
			it = p_list->erase(it);
		}
		else
		{
			it++;
		}
	}
}