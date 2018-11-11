/*@Rock 11.11

This class will calculate a path between original tile and target tile
A* path find is used
*/

#pragma once
#include "kitten/event_system/Event.h"
class PathFind
{
public:
	PathFind();
	~PathFind();

	kitten::Event::TileList getPath(std::pair<int,int> p_start, std::pair<int, int> p_end, int p_mv);
private:
	struct node
	{
		std::pair<int, int> tile;
		int cost;
		int estimate;
		int weight;
		node* parent;
	};

	int m_maxX;
	int m_maxZ;
	node* m_start;
	bool m_isClear;

	std::pair<int, int> m_target;

	int m_mv;
	std::vector<node*> m_openList;
	std::vector<node*> m_closedList;

	node* getNodeInOpen();
	void getNeighbour(node* p_node);
	bool checkTile(std::pair<int, int> p_tile, int p_cost);
	void addNodeToOpen(std::pair<int, int> p_tile, int p_cost, node* p_parent);
	kitten::Event::TileList getList(node* p_n);
	void clear();
};