#include "TileFliter.h"

TileFilter::TileFilter()
{
}

TileFilter::~TileFilter()
{
}

void TileFilter::filter(kitten::Event::TileList * p_list)
{
	assert(false);
}

void TileFilter::enable()
{
	m_enabled = true;
}

void TileFilter::disable()
{
	m_enabled = false;
}
