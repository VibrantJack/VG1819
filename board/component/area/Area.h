//@Rock
//This is a component of the board manager. 
//It finds an area based on pivot point and source.
//It will be use when area ability is selected

#pragma once
#include "kitten/K_Common.h"
#include "kitten/event_system/Event.h"
#include "board/component/area/AreaPattern.h"

#define POINT_AREA "point"
#define SPAN_AREA "span"
#define SQUARE_AREA "square"
#define LINEV_AREA "lineV"
#define LINEH_AREA "lineH"
#define TRIANGLE_AREA "triangle"
#define PATH "path"

#define ORIGIN "tileAtOrigin"
#define AREA_LEN "area_len"
#define AREA_MIN "area_min"
#define AREA_MAX "area_max"
#define AREA_MODE "area_mode"
#define AREA_FIX "area_fix"

class Area
{
private:
	std::unordered_map<std::string, AreaPattern*> m_map;
	AreaInfo* m_info;
	bool m_active;
	bool m_fix;
	std::string m_mode;
public:
	Area();
	~Area();

	void setPattern(kitten::Event * p_data);
	void removePattern();

	bool isActive();
	kitten::Event::TileList getTileListWithPivot(kitten::K_GameObject* p_pivot);

};