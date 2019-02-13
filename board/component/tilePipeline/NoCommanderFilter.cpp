#include "TileFliter.h"

/*
void NoCommanderFilter::filter(kitten::Event::TileList * p_list)
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
			continue;
		}

		kitten::K_GameObject* u = tileGO->getComponent<TileInfo>()->getUnit();

		if (!u->getComponent<unit::Unit>()->isCommander())
		{
			it = p_list->erase(it);
		}
		else
		{
			it++;
		}
	}
}*/


bool NoCommanderFilter::shouldRemove(kitten::K_GameObject * p_tileGO)
{
	if (p_tileGO->getComponent<TileInfo>()->hasUnit())
	{
		kitten::K_GameObject* u = p_tileGO->getComponent<TileInfo>()->getUnit();

		if (!u->getComponent<unit::Unit>()->isCommander())
			return true;
	}
	return false;
}