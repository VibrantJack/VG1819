
//@Rock
//This is a component of the board creator. 
//It keeps tile's coordinate.
//It will be used when unit use range ability, like move


#pragma once
#include "kitten/K_Component.h"
#include "board/component/BoardCreator.h"
#include "unit/Unit.h"
#include "kitten/event_system/EventManager.h"

class Range
{
public:
	static kitten::Event::TileList getTilesInRange(kitten::Event * p_data);

	static kitten::Event::TileList getTilesInRange
	(kitten::K_GameObject* p_tileAtOrigin,
		int p_minRange, int p_maxRange);
private:
	static void findNeighbour
	(std::map<std::pair<int, int>, int>* p_tilesAndRange, 
		std::pair<int, int> p_currentTile, 
		int p_distance, int p_minRange, int p_maxRange);

	static void removeUnit(kitten::Event::TileList* p_list);
};