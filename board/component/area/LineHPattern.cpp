#include "AreaPattern.h"

kitten::Event::TileList LineHPattern::getTileList(AreaInfo * p_info)
{
	kitten::Event::TileList list;
	
	getInfo(p_info);

	int half = m_len / 2;
	switch (m_dir)
	{
	case 1:
	case 2:
		for (int i = -half; i <= half; i++)
		{
			int tx = m_posP.first + i;
			if (tx < 0)
			{
				continue;
			}
			else if (tx >= m_d.first)
			{
				break;
			}
			else
			{
				list.push_back(std::make_pair(tx, m_posP.second));
			}
		}
		break;
	case 3:
	case 4:
		for (int i = -half; i <= half; i++)
		{
			int tz = m_posP.second + i;
			if (tz < 0)
			{
				continue;
			}
			else if (tz >= m_d.second)
			{
				break;
			}
			else
			{
				list.push_back(std::make_pair(m_posP.first, tz));
			}
		}
		break;
	}

	return list;
}