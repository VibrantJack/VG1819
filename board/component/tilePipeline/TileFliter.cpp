#include "TileFliter.h"

TileFilter::TileFilter(TilePipeline* p_p):m_pipe(p_p)
{
}

TileFilter::~TileFilter()
{
}

void TileFilter::filter(kitten::Event::TileList * p_list)
{
	//not enable, then not apply
	if (!m_enabled)
		return;

	auto it = p_list->begin();
	while (it != p_list->end())
	{
		kitten::K_GameObject* tileGO = BoardManager::getInstance()->getTile(it->first, it->second);
		if (this->shouldRemove(tileGO))
			it = p_list->erase(it);
		else
			it++;
	}
}

void TileFilter::enable()
{
	m_enabled = true;
}

void TileFilter::disable()
{
	m_enabled = false;
}

