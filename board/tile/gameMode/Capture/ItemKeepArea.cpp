#include "ItemKeepArea.h"

//get 10 items to win
static const int s_PointPerItem = 10;

ItemKeepArea::ItemKeepArea()
{
}

ItemKeepArea::~ItemKeepArea()
{
}

void ItemKeepArea::check()
{
	//should only have 2 keep area on the map
	assert(m_tileList.size() == 2);


}
