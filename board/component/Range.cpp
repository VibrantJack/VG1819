#include "Range.h"
#include "board/tile/TileInfo.h"
#include "board/BoardManager.h"
#include <iostream>

Range::Range()
{
}

Range::~Range()
{
}

void Range::setDimension(int p_x, int p_z)
{
	m_x = p_x;
	m_z = p_z;
}

kitten::Event::TileList Range::getTilesInRange(kitten::Event * p_data)
{
	kitten::K_GameObject * tileAtOrigin = p_data->getGameObj("tileAtOrigin");
	m_min = p_data->getInt("min_range");
	m_max = p_data->getInt("max_range");
	m_origin = tileAtOrigin->getComponent<TileInfo>()->getPos();

	if (p_data->getInt("path") == TRUE)
	{
		return getPathRange();
	}

	return getList();
}

kitten::Event::TileList Range::getTilesInRange(kitten::K_GameObject * p_tileAtOrigin, int p_minRange, int p_maxRange)
{
	m_min = p_minRange;
	m_max = p_maxRange;
	m_origin = p_tileAtOrigin->getComponent<TileInfo>()->getPos();

	return getList();
}

kitten::Event::TileList Range::getList() const
{
	kitten::Event::TileList list;

	for (int xStep = m_max; xStep >= -m_max; xStep--)
	{
		int alter = m_max - xStep;
		if (xStep < 0)
			alter = xStep + m_max;

		for (int zStep = -alter; zStep <= alter; zStep++)
		{
			int x = m_origin.first + xStep;
			int z = m_origin.second + zStep;
			std::cout << "tile:" << x << " , " << z << std::endl;
			addTile(&list, x, z);
		}
	}

	return list;
}

void Range::addTile(kitten::Event::TileList * p_list, int p_tileX, int p_tileZ) const
{
	//within dimension
	if (p_tileX >= 0 && p_tileX < m_x && p_tileZ >= 0 && p_tileZ < m_z)
	{
		//within range
		int distance = 0;
		distance += std::abs(p_tileX - m_origin.first);
		distance += std::abs(p_tileZ - m_origin.second);
		if (distance >= m_min && distance <= m_max)
		{
			p_list->push_back(std::make_pair(p_tileX,p_tileZ));
		}
	}
}

kitten::Event::TileList Range::getPathRange() const
{
	std::map<std::pair<int, int>, int> tilesAndRange;

	int x = m_origin.first;
	int z = m_origin.second;

	checkTile(&tilesAndRange, std::pair<int, int>(x - 1, z), 0);
	checkTile(&tilesAndRange, std::pair<int, int>(x + 1, z), 0);
	checkTile(&tilesAndRange, std::pair<int, int>(x, z - 1), 0);
	checkTile(&tilesAndRange, std::pair<int, int>(x, z + 1), 0);

	kitten::Event::TileList list;
	for (auto it : tilesAndRange)
	{
		if (it.second >= m_min && it.second <= m_max)
		{
			list.push_back(it.first);
		}
	}
	return list;
}

void Range::checkTile(std::map<std::pair<int, int>, int>* p_tilesAndRange, std::pair<int, int> p_currentTile, int p_distance) const
{
	//out of board
	if (p_currentTile.first >= m_x || p_currentTile.first < 0 || p_currentTile.second >= m_z || p_currentTile.second < 0)
		return;

	//get tile info
	TileInfo* info = BoardManager::getInstance()->getTile(p_currentTile.first, p_currentTile.second)->getComponent<TileInfo>();

	//dont add tile has unit exclude origin tile
	if (info->hasUnit())
		return;

	//get mv cost
	int cost = info->getMVCost();

	//distance is preivouse tile cost,add it
	cost += p_distance;

	//if the distance is excess the max range, we dont go further
	if (cost > m_max)
		return;

	//check if the tile is already in the list
	auto found = p_tilesAndRange->find(p_currentTile);
	if (found != p_tilesAndRange->end())
	{
		//it's in the list, then compare the distance
		if (cost < found->second)
		{
			found->second = cost;
			//always keep the least distance
		}
		else//avoid repeat check
			return;
	}
	else
	{
		//not in the list, add it
		p_tilesAndRange->insert(std::make_pair(p_currentTile, cost));
	}

	//then check neighbour
	int x = p_currentTile.first;
	int z = p_currentTile.second;

	checkTile(p_tilesAndRange, std::pair<int, int>(x - 1, z), cost);
	checkTile(p_tilesAndRange, std::pair<int, int>(x + 1, z), cost);
	checkTile(p_tilesAndRange, std::pair<int, int>(x, z - 1), cost);
	checkTile(p_tilesAndRange, std::pair<int, int>(x, z + 1), cost);
}

