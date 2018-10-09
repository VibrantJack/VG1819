#include "Range.h"

kitten::Event::TileList Range::getTilesInRange(kitten::K_GameObject * p_tileAtOrigin, int p_minRange, int p_maxRange, kitten::K_GameObject * p_tileList[15][15])
{
	std::map<std::pair<int, int>, int> tilesAndRange;

	//find the coordinates for the tile at origin
	std::pair<int, int> originCoord = findOrigin(p_tileAtOrigin, p_tileList);

	//find tiles
	findNeighbour(&tilesAndRange,originCoord,0,p_minRange,p_maxRange);

	//add it to the highlight list 
	kitten::Event::TileList list;
	for (auto it = tilesAndRange.begin(); it!=tilesAndRange.end();it++)
	{
		list.push_back(it->first);
	}

	return list;
}

std::pair<int, int> Range::findOrigin(const kitten::K_GameObject * p_tileAtOrigin, kitten::K_GameObject * p_tileList[15][15])
{
	for (int x = 0; x < 15; x++)
	{
		for (int z = 0; z < 15; z++)
		{
			if (p_tileAtOrigin == p_tileList[x][z])
				return std::pair<int, int>(x, z);
		}
	}
	//not find tile
	assert(false);
	return std::pair<int, int>();
}

void Range::findNeighbour(std::map<std::pair<int, int>, int>* p_tilesAndRange, std::pair<int, int> p_currentTile, int p_distance, int p_minRange, int p_maxRange)
{
	//if the distance is excess the max range, we dont go further
	if (p_distance > p_maxRange)
		return;
	//if the distance is within the range
	if (p_distance >= p_minRange && p_distance <= p_maxRange)
	{
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

