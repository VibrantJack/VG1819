#include "Range.h"
#include "board/tile/TileInfo.h"
#include "board/BoardManager.h"


kitten::Event::TileList Range::getTilesInRange(kitten::Event * p_data)
{
	kitten::K_GameObject * tileAtOrigin = p_data->getGameObj("tileAtOrigin");
	int min = p_data->getInt("min_range");
	int max = p_data->getInt("max_range");

	//get list in range
	kitten::Event::TileList list = getTilesInRange(tileAtOrigin, min, max);

	//remove tiles that has something on it if this is used for moving
	std::string use = p_data->getString("use");
	if (use == "move")
	{
		removeUnit(&list);
	}

	return list;
}

kitten::Event::TileList Range::getTilesInRange(kitten::K_GameObject * p_tileAtOrigin, int p_minRange, int p_maxRange)
{
	std::map<std::pair<int, int>, int> tilesAndRange;

	//find the coordinates for the tile at origin
	std::pair<int, int> originCoord = p_tileAtOrigin->getComponent<TileInfo>()->getPos();

	//find tiles
	findNeighbour(&tilesAndRange,originCoord,0,p_minRange,p_maxRange);

	//add it to the highlight list 
	kitten::Event::TileList list;
	for (auto it = tilesAndRange.begin(); it!=tilesAndRange.end();it++)
	{
		int d = it->second;
		//if the distance is within the range
		if (d >= p_minRange && d <= p_maxRange)
		{
			list.push_back(it->first);
		}
	}

	return list;
}

void Range::findNeighbour(std::map<std::pair<int, int>, int>* p_tilesAndRange, std::pair<int, int> p_currentTile, int p_distance, int p_minRange, int p_maxRange)
{
	//if the distance is excess the max range, we dont go further
	if (p_distance > p_maxRange)
		return;

	//check if the tile is already in the list
	bool exist = p_tilesAndRange->find(p_currentTile) != p_tilesAndRange->end();
	if (exist)
	{
		//it's in the list, then compare the distance
		if (p_distance < (*p_tilesAndRange)[p_currentTile])
		{
			(*p_tilesAndRange)[p_currentTile] = p_distance;
			//always keep the least distance
		}
		else
			return;
		//if the list already has smaller distance, terminal

	}
	else
	{
		//not find,then add it to the list
		p_tilesAndRange->insert(std::pair<std::pair<int, int>, int>(p_currentTile, p_distance));
	}

	//then check neighbour
	int x = p_currentTile.first;
	int z = p_currentTile.second;

	if (x > 0)//check right
	{
		findNeighbour(p_tilesAndRange, std::pair<int, int>(x-1, z), p_distance + 1, p_minRange, p_maxRange);
	}
	if (x < 14)//check left
	{
		findNeighbour(p_tilesAndRange, std::pair<int, int>(x+1, z), p_distance + 1, p_minRange, p_maxRange);
	}
	if (z > 0)//check down
	{
		findNeighbour(p_tilesAndRange, std::pair<int, int>(x, z-1), p_distance + 1, p_minRange, p_maxRange);
	}
	if (z < 14)//check up
	{
		findNeighbour(p_tilesAndRange, std::pair<int, int>(x, z+1), p_distance + 1, p_minRange, p_maxRange);
	}
}

void Range::removeUnit(kitten::Event::TileList* p_list)
{
	//remove tiles that has unit
	auto it = p_list->begin();
	while (it != p_list->end())
	{
		kitten::K_GameObject* tileGO = BoardManager::getInstance()->getTile(it->first, it->second);
		if (tileGO->getComponent<TileInfo>()->hasUnit())
		{
			it = p_list->erase(it);
		}
		else
		{
			it++;
		}
	}
}

