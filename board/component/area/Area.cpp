#include "Area.h"
#include "unit/Unit.h"
Area::Area()
{
	m_info = new AreaInfo();
	m_active = false;
	m_fix = false;

	AreaPattern* ap = new PointPattern();
	std::string name = POINT_AREA;
	m_map[name] = ap;

	ap = new SpanPattern();
	name = SPAN_AREA;
	m_map[name] = ap;

	ap = new LineVPattern();
	name = LINEV_AREA;
	m_map[name] = ap;

	ap = new LineHPattern();
	name = LINEH_AREA;
	m_map[name] = ap;

	ap = new SquarePattern();
	name = SQUARE_AREA;
	m_map[name] = ap;

	ap = new TrianglePattern();
	name = TRIANGLE_AREA;
	m_map[name] = ap;

	ap = new PathPattern();
	name = PATH;
	m_map[name] = ap;
}

Area::~Area()
{
	delete m_info;//delete info
	for (auto it = m_map.begin(); it != m_map.end(); it++)//delete all pattern
	{
		delete it->second;
	}
}

void Area::setPattern(kitten::Event * p_data)
{
	m_info->m_origin = p_data->getGameObj(ORIGIN);

	m_mode = p_data->getString(AREA_MODE);
	int fix = p_data->getInt(AREA_FIX);
	if(fix == TRUE)
	{
		m_fix = true;
		m_info->m_pivot = m_info->m_origin;
	}

	if (m_mode == SPAN_AREA || m_mode == SQUARE_AREA)
	{
		m_info->m_minLen = p_data->getInt(AREA_MIN);
		m_info->m_maxLen = p_data->getInt(AREA_MAX);
	}
	else if (m_mode == POINT_AREA)
	{
		//nothing to add
	}
	else
	{
		m_info->m_length = p_data->getInt(AREA_LEN);
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
	return m_map[m_mode]->getTileList(m_info);
}
