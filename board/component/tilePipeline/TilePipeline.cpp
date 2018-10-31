#include "TilePipeline.h"

TilePipeline::TilePipeline()
{
	m_filterList =  new std::unordered_map<std::string, TileFilter*>();

	//init all filter
	TileFilter* filter;

	filter = new UnitFilter();
	m_filterList->insert(std::make_pair("unit",filter));

	filter = new NoUnitFilter();
	m_filterList->insert(std::make_pair("no_unit", filter));

	filter = new OwnedTileFilter();
	m_filterList->insert(std::make_pair("owned_tile", filter));
}

TilePipeline::~TilePipeline()
{
	for (auto it = m_filterList->begin(); it != m_filterList->end(); it++)
	{
		delete it->second;
	}
}

void TilePipeline::filterList(kitten::Event::TileList * p_list)
{
	for (auto it = m_filterList->begin(); it != m_filterList->end(); it++)
	{
		it->second->filter(p_list);
	}
}

void TilePipeline::useFilter(const std::string & p_filter)
{
	m_filterList->at(p_filter)->enable();
}

void TilePipeline::resetFilter()
{
	for (auto it = m_filterList->begin(); it != m_filterList->end(); it++)
	{
		it->second->disable();
	}
}
