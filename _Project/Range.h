#pragma once
#include "kitten/K_Component.h"
#include "_Project/BoardCreator.h"
#include "unit/Unit.h"

//Rock
//This is a component of the board creator. 
//It keeps tile's coordinate.
//It will be used when unit use range ability, like move

class Range
{
public:
	static kitten::Event::TileList getTilesInRange
	(kitten::K_GameObject* p_tileAtOrigin, 
		int p_minRange, int p_maxRange, 
		kitten::K_GameObject* p_tileList[15][15]);
private:
	static std::pair<int, int> findOrigin(const kitten::K_GameObject * p_tileAtOrigin, kitten::K_GameObject * p_tileList[15][15]);
	static void findNeighbour
	(std::map<std::pair<int, int>, int>* p_tilesAndRange, 
		std::pair<int, int> p_currentTile, 
		int p_distance, int p_minRange, int p_maxRange);
};