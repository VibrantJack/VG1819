/*Rock 10.26

The filter that will remove tiles from list.

*/

#pragma once
#include "board/BoardManager.h"

class TilePipeline;
class TileFilter
{
public:
	TileFilter(TilePipeline* p_p);
	~TileFilter();

	virtual void filter(kitten::Event::TileList* p_list);
	void enable();
	void disable();
protected:
	TilePipeline* m_pipe;
	bool m_enabled = false;
};

class UnitFilter : public TileFilter
{//remove tiles that has unit on it
public:
	UnitFilter(TilePipeline* p_p) :TileFilter(p_p) {};
	void filter(kitten::Event::TileList* p_list);
};

class OwnedTileFilter : public TileFilter
{//remove tiles that has owner
public:
	OwnedTileFilter(TilePipeline* p_p) :TileFilter(p_p) {};
	void filter(kitten::Event::TileList* p_list);
};

class UnownedTileFilter : public TileFilter
{//remove tiles that owner isn't player
public:
	UnownedTileFilter(TilePipeline* p_p) :TileFilter(p_p) {};
	void filter(kitten::Event::TileList* p_list);
};

class NoUnitFilter : public TileFilter
{//remove tiles that doesn't have unit
public:
	NoUnitFilter(TilePipeline* p_p) :TileFilter(p_p) {};
	void filter(kitten::Event::TileList* p_list);
};

class NoCommanderFilter : public TileFilter
{//remove tiles that doesn't have commander
public:
	NoCommanderFilter(TilePipeline* p_p) :TileFilter(p_p) {};
	void filter(kitten::Event::TileList* p_list);
};

class EnemyFilter : public TileFilter
{//remove tiles that has enemy
public:
	EnemyFilter(TilePipeline* p_p) :TileFilter(p_p) {};
	void filter(kitten::Event::TileList* p_list);
};

class AllyFilter : public TileFilter
{//remove tiles that has enemy
public:
	AllyFilter(TilePipeline* p_p) :TileFilter(p_p) {};
	void filter(kitten::Event::TileList* p_list);
};

