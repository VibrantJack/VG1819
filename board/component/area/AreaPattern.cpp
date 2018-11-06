#include "AreaPattern.h"
#include "board/BoardManager.h"

void AreaPattern::getInfo(AreaInfo * p_info)
{
	//get pivot
	m_posP = p_info->m_pivot->getComponent<TileInfo>()->getPos();

	//get origin
	m_posO = p_info->m_origin->getComponent<TileInfo>()->getPos();

	//get length
	m_len = p_info->m_length;

	//get boundary
	m_d = BoardManager::getInstance()->getDimension();

	//get direction
	int x = m_posP.first - m_posO.first;
	int z = m_posP.second - m_posO.second;
	if (x == 0 && z > 0)//positive z direction
	{
		m_dir = 1;
	}
	else if (x == 0 && z < 0)//negative z direction
	{
		m_dir = 2;
	}
	else if (z == 0 && x > 0)//positive x direction
	{
		m_dir = 3;
	}
	else if (z == 0 && x < 0)//negative x direction
	{
		m_dir = 4;
	}
}
