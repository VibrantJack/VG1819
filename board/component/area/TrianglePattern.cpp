#include "AreaPattern.h"
kitten::Event::TileList TrianglePattern::getTileList(AreaInfo * p_info)
{
	kitten::Event::TileList list;

	getInfo(p_info);

	int span = 0;
	switch (m_dir)
	{
	case 1:
	case 2:
		for (int i = 0; i < m_len; i++)
		{
			int tz;
			if (m_dir == 1)
				tz = m_posP.second + i;//z value of next tile
			else
				tz = m_posP.second - i;
			if (tz >= 0 && tz < m_d.second)
			{
				//span to sides
				for (int j = -span; j <= span; j++)
				{
					int tx = m_posP.first + j;
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
						list.push_back(std::make_pair(tx, tz));
					}
				}
				span++;
			}
			else
			{
				break;
			}
		}
		break;
	case 3:
	case 4:
		for (int i = 0; i < m_len; i++)
		{
			int tx;
			if (m_dir == 3)
				tx = m_posP.first + i;//z value of next tile
			else
				tx = m_posP.first - i;
			if (tx >= 0 && tx < m_d.first)
			{
				//span to sides
				for (int j = -span; j <= span; j++)
				{
					int tz = m_posP.second + j;
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
						list.push_back(std::make_pair(tx, tz));
					}
				}
				span++;
			}
			else
			{
				break;
			}
		}
		break;
	}

	return list;
}