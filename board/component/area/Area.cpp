#include "Area.h"
#include "unit/Unit.h"
Area::Area()
{
	m_map = new std::unordered_map<std::string, AreaPattern*>();
	m_info = new AreaInfo();
	m_active = false;
	m_fix = false;

	AreaPattern* ap = new PointPattern();
	std::string name = "point";
	m_map->insert(std::make_pair(name, ap));

	ap = new SpanPattern();
	name = "span";
	m_map->insert(std::make_pair(name, ap));

	ap = new LineVPattern();
	name = "lineV";
	m_map->insert(std::make_pair(name, ap));

	ap = new LineHPattern();
	name = "lineH";
	m_map->insert(std::make_pair(name, ap));

	ap = new SquarePattern();
	name = "square";
	m_map->insert(std::make_pair(name, ap));

	ap = new TrianglePattern();
	name = "triangle";
	m_map->insert(std::make_pair(name, ap));
}

Area::~Area()
{
	delete m_info;//delete info
	for (auto it = m_map->begin(); it != m_map->end(); it++)//delete all pattern
	{
		delete it->second;
	}
}

void Area::setPattern(kitten::Event * p_data)
{
	m_info->m_origin = p_data->getGameObj("tileAtOrigin");

	m_mode = p_data->getString("area_mode");
	int fix = p_data->getInt("area_fix");
	if(fix == 1)
	{
		m_fix = true;
		m_info->m_pivot = m_info->m_origin;
	}

	if (m_mode == "span" || m_mode == "square")
	{
		m_info->m_minLen = p_data->getInt("area_min");
		m_info->m_maxLen = p_data->getInt("area_max");
	}
	else if (m_mode == "point")
	{
		//nothing to add
	}
	else
	{
		m_info->m_length = p_data->getInt("area_len");
	}

	m_active = true;
}

void Area::removePattern()
{
	m_active = false;
	m_fix = false;
}

bool Area::isActive()
{
	return m_active;
}

kitten::Event::TileList Area::getTileListWithPivot(kitten::K_GameObject * p_pivot)
{
	if(!m_fix)
		m_info->m_pivot = p_pivot;
	return m_map->at(m_mode)->getTileList(m_info);
}
