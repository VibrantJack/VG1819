#include "LandInformation.h"

LandInformation::LandInformation(TileType p_Type, const std::string & p_TexturePath, int p_mvCost, const std::string & p_description)
	:m_Type(p_Type),
	m_TexturePath(p_TexturePath),
	m_mvCost(p_mvCost),
	m_description(p_description)
{

}
