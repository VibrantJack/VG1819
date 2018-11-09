#include "AreaPattern.h"

kitten::Event::TileList LineVPattern::getTileList(AreaInfo * p_info)
{
	kitten::Event::TileList list;
	
	getInfo(p_info);

	switch (m_dir)
	{
	case 1:
		for (int i = 0; i < m_len; i++)
		{
			int tz = m_posP.second + i;//z value of next tile
			if (tz < m_d.second)
			{
				list.push_back(std::make_pair(m_posP.first, tz));
			}
			else
			{
				break;
			}
		}
		break;
	case 2:
		for (int i = 0; i < m_len; i++)
		{
			int tz = m_posP.second - i;//z value of next tile
			if (tz >= 0)
			{
				list.push_back(std::make_pair(m_posP.first, tz));
			}
			else
			{
				break;
			}
		}
		break;
	case 3:
		for (int i = 0; i < m_len; i++)
		{
			int tx = m_posP.first + i;//z value of next tile
			if (tx < m_d.first)
			{
				list.push_back(std::make_pair(tx, m_posP.second));
			}
			else
			{
				break;
			}
		}
		break;
	case 4:
		for (int i = 0; i < m_len; i++)
		{
			int tx = m_posP.first - i;//z value of next tile
			if (tx >= 0)
			{
				list.push_back(std::make_pair(tx, m_posP.second));
			}
			else
			{
				break;
			}
		}
		break;
	default:
		break;
	}

	return list;
}