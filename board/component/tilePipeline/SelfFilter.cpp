#include "TileFliter.h"

void SelfFilter::filter(kitten::Event::TileList * p_list)
{
	if (!m_enabled)
		return;

	unit::Unit* source = m_pipe->m_source;

	//remove tiles that is source
	auto it = p_list->begin();
	while (it != p_list->end())
	{
		kitten::K_GameObject* tileGO = BoardManager::getInstance()->getTile(it->first, it->second);

		kitten::K_GameObject* u = tileGO->getComponent<TileInfo>()->getUnit();

		if (u->getComponent<unit::Unit>() == source)//source
		{
			it = p_list->erase(it);
			break;
		}
		else
		{
			it++;
		}
	}
}