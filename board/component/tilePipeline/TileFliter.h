/*Rock 10.26

The filter that will remove tiles from list.

*/

#pragma once
#include "board/BoardManager.h"

class TileFilter
{
public:
	TileFilter();
	~TileFilter();

	virtual void filter(kitten::Event::TileList* p_list);
	void enable();
	void disable();
protected:
	bool m_enabled = false;
};

class UnitFilter : public TileFilter
{//remove tiles that has unit on it
public:
	void filter(kitten::Event::TileList* p_list);
};

class OwnedTileFilter : public TileFilter
{//remove tiles that has owner
public:
	void filter(kitten::Event::TileList* p_list);
};

class NoUnitFilter : public TileFilter
{//remove tiles that doesn't have unit
public:
	void filter(kitten::Event::TileList* p_list);
};

class NoCommanderFilter : public TileFilter
{//remove tiles that doesn't have commander
public:
	void filter(kitten::Event::TileList* p_list);
};

