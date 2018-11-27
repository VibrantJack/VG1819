#pragma once
#include "unit/unitComponent/CooldownRecorder.h"

unit::CooldownRecorder::CooldownRecorder()
{
}

unit::CooldownRecorder::~CooldownRecorder()
{
}

void unit::CooldownRecorder::addCD(AbilityDescription* p_ad)
{
	if (p_ad->m_intValue.find(UNIT_CD) != p_ad->m_intValue.end())
	{//check if the ability has cd
		int cd = p_ad->m_intValue[UNIT_CD];

		m_cdmap.insert(std::make_pair(p_ad, cd));
	}
}

void unit::CooldownRecorder::cancelCD(AbilityDescription* p_ad)
{
	if (m_cdmap.size() == 0)
		return;

	if (m_cdmap.find(p_ad) != m_cdmap.end())
	{//find it and remove it
		m_cdmap.erase(p_ad);
	}
}

int unit::CooldownRecorder::checkCD(AbilityDescription* p_ad)
{
	std::unordered_map<AbilityDescription*, int>::iterator it = m_cdmap.find(p_ad);
	if (it != m_cdmap.end())
	{//find it and return its cd
		return it->second;
	}
	else
	{//doesn't find
		return 0;
	}
}

void unit::CooldownRecorder::changeCDByEffect(AbilityDescription* p_ad, int p_cd)
{
	//find target
	std::unordered_map<AbilityDescription*, int>::iterator it = m_cdmap.find(p_ad);
	if (it != m_cdmap.end())
	{//find it and change its cd
		it->second += p_cd;
	}
	else
	{//doesn't find
		if (p_cd > 0)//it is gaining cd
		{
			m_cdmap.insert(std::make_pair(p_ad, p_cd));
		}
	}
}

void unit::CooldownRecorder::reduceCD()
{
	if (m_cdmap.size()==0)//no cd yet
	{
		return;
	}

	std::vector<AbilityDescription*> toBeRemove;
	for (auto it = m_cdmap.begin(); it!=m_cdmap.end(); it++)
	{
		it->second--;//reduce cd by 1
		if (it->second <= 0)
		{//remove cd
			toBeRemove.push_back(it->first);
		}
	}
	for (int i = 0; i < toBeRemove.size(); i++)
	{
		m_cdmap.erase(toBeRemove[i]);
	}
}