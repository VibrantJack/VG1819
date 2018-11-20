#include "TilePipeline.h"

TilePipeline::TilePipeline()
{
	//init all filter
	TileFilter* filter;

	filter = new UnitFilter();
	m_filterList[FILTER_UNIT] = filter;

	filter = new NoUnitFilter();
	m_filterList[FILTER_NO_UNIT] = filter;

	filter = new OwnedTileFilter();
	m_filterList[FILTER_OWNED_TILE] = filter;

	filter = new NoCommanderFilter();
	m_filterList[FILTER_NO_COMMANDER] = filter;
}

TilePipeline::~TilePipeline()
{
	for (auto it = m_filterList.begin(); it != m_filterList.end(); it++)
	{
		delete it->second;
	}
}

void TilePipeline::filterList(kitten::Event::TileList * p_list)
{
	for (auto it = m_filterList.begin(); it != m_filterList.end(); it++)
	{
		it->second->filter(p_list);
	}
}

void TilePipeline::useFilter(const std::string & p_filter)
{
	m_filterList[p_filter]->enable();
}

void TilePipeline::resetFilter()
{
	for (auto it = m_filterList.begin(); it != m_filterList.end(); it++)
	{
		it->second->disable();
	}
}
