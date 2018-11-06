//@Rock
//This is a component of Area. 
//It handles finding tile list.
//the method is different based on what pattern it is

#pragma once
#include "kitten/K_Common.h"
#include "kitten/event_system/Event.h"
#include "board/tile/TileInfo.h"

struct AreaInfo
{
	kitten::K_GameObject* m_pivot;
	kitten::K_GameObject* m_origin;

	int m_length;//for lineV, lineH, square, triangle

	int m_minLen;
	int m_maxLen;//for span
};

class AreaPattern
{
public:
	std::pair<int, int> m_posP;//pivot
	std::pair<int, int> m_posO;//origin
	int m_len;//length
	std::pair<int, int> m_d;//boundary
	int m_dir;//pivot is at m_dir direction of origin

	virtual kitten::Event::TileList getTileList(AreaInfo* p_info) = 0;
	void getInfo(AreaInfo* p_info);
};

class PointPattern : public AreaPattern
{
public:
	kitten::Event::TileList getTileList(AreaInfo* p_info);
};

class SpanPattern : public AreaPattern
{
public:
	kitten::Event::TileList getTileList(AreaInfo* p_info);
};

class LineVPattern : public AreaPattern
{
public:
	kitten::Event::TileList getTileList(AreaInfo* p_info);
};

class LineHPattern : public AreaPattern
{
public:
	kitten::Event::TileList getTileList(AreaInfo* p_info);
};

class SquarePattern : public AreaPattern
{
public:
	kitten::Event::TileList getTileList(AreaInfo* p_info);
};

class TrianglePattern : public AreaPattern
{
public:
	kitten::Event::TileList getTileList(AreaInfo* p_info);
};
