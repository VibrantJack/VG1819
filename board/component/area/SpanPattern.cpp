#include "AreaPattern.h"
#include "board/BoardManager.h"
kitten::Event::TileList SpanPattern::getTileList(AreaInfo * p_info)
{
	getInfo(p_info);

	//using range;
	Range* r = new Range();
	r->setDimension(m_d.first, m_d.second);

	int min = p_info->m_minLen;
	int max = p_info->m_maxLen;

	kitten::Event::TileList list = r->getTilesInRange(p_info->m_pivot, min, max);
	
	delete r;

	return list;
}