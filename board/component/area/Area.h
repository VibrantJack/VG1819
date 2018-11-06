//@Rock
//This is a component of the board manager. 
//It finds an area based on pivot point and source.
//It will be use when area ability is selected

#pragma once
#include "kitten/K_Common.h"
#include "kitten/event_system/Event.h"
#include "board/component/area/AreaPattern.h"

class Area
{
private:
	std::unordered_map<std::string, AreaPattern*>* m_map;
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