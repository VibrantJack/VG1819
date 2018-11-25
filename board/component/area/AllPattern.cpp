#include "AreaPattern.h"
#include "board/BoardManager.h"
kitten::Event::TileList AllPattern::getTileList(AreaInfo * p_info)
{
	//return the range
	return BoardManager::getInstance()->getRange();
}