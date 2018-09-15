#include "UnitData.h"



UnitData::UnitData()
{
}

UnitData::UnitData(std::string p_name, int p_HP, int p_MV, int p_IN, int p_Cost, UnitSize p_size, std::vector<std::string> p_tags, std::vector<std::string> p_AD, std::vector<std::string> p_SD)
{
	m_name = p_name;
	m_HP = p_HP;
	m_MV = p_MV;
	m_IN = p_IN;
	m_Cost = p_Cost;
	m_size = p_size;
	m_tags = p_tags;
	m_abilityDescription = p_AD;
	m_statusDescription = p_SD;
}


UnitData::~UnitData()
{
}
