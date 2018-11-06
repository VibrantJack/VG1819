#include "AreaPattern.h"

kitten::Event::TileList SquarePattern::getTileList(AreaInfo * p_info)
{
	kitten::Event::TileList list;

	getInfo(p_info);

	int half = m_len / 2;

	for (int ix = -half; ix <= half; ix++)//start from left most
	{
		int tx = m_posP.first + ix;
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
			for (int iz = -half; iz <= half; iz++)//start from bottom
			{
				int tz = m_posP.second + iz;
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
		}
	}

	return list;
}