#include "TileFliter.h"

/*
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
*/

bool AllyFilter::shouldRemove(kitten::K_GameObject * p_tileGO)
{
	if (p_tileGO->getComponent<TileInfo>()->hasUnit())
	{
		kitten::K_GameObject* u = p_tileGO->getComponent<TileInfo>()->getUnit();
		int id = u->getComponent<unit::Unit>()->m_clientId;
		if (id == m_pipe->m_source->m_clientId)
			return true;
	}
	return false;
}