#include "TileFliter.h"

void AllyFilter::filter(kitten::Event::TileList * p_list)
{
	if (!m_enabled)
		return;

	unit::Unit* source = m_pipe->m_source;

	auto it = p_list->begin();
	while (it != p_list->end())
	{
		//remove tiles that doesn't have unit
		kitten::K_GameObject* tileGO = BoardManager::getInstance()->getTile(it->first, it->second);
		if (!tileGO->getComponent<TileInfo>()->hasUnit())
		{
			it = p_list->erase(it);
			continue;
		}

		kitten::K_GameObject* u = tileGO->getComponent<TileInfo>()->getUnit();

		if (u->getComponent<unit::Unit>()->m_clientId == source->m_clientId)//ally
		{
			it = p_list->erase(it);
		}
		else
		{
			it++;
		}
	}
}