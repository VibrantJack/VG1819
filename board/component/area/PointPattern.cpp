#include "AreaPattern.h"

kitten::Event::TileList PointPattern::getTileList(AreaInfo * p_info)
{
	//return itself
	getInfo(p_info);

	kitten::Event::TileList list;
	list.push_back(m_posP);

	return list;
}