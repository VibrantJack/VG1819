#include "TileFliter.h"

TileFilter::TileFilter(TilePipeline* p_p):m_pipe(p_p)
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

