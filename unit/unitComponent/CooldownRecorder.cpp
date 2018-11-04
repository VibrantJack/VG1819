#pragma once
#include "unit/unitComponent/CooldownRecorder.h"

unit::CooldownRecorder::CooldownRecorder()
{
	m_cdmap = nullptr;
}

unit::CooldownRecorder::~CooldownRecorder()
{
	if (m_cdmap != nullptr)
		delete m_cdmap;
}

void unit::CooldownRecorder::addCD(AbilityDescription* p_ad)
{
	if (p_ad->m_intValue.find("cd") != p_ad->m_intValue.end())
	{//check if the ability has cd
		int cd = p_ad->m_intValue["cd"];

		if (m_cdmap == nullptr)
		{//create map
			m_cdmap = new std::unordered_map<AbilityDescription*, int>();
		}

		m_cdmap->insert(std::make_pair(p_ad, cd));
	}
}

void unit::CooldownRecorder::cancelCD(AbilityDescription* p_ad)
{
	if (m_cdmap == nullptr)
		return;

	if (m_cdmap->find(p_ad) != m_cdmap->end())
	{//find it and remove it
		m_cdmap->erase(p_ad);
	}
}

int unit::CooldownRecorder::checkCD(AbilityDescription* p_ad)
{
	if (m_cdmap == nullptr)//no cd yet
	{
		return 0;
	}

	std::unordered_map<AbilityDescription*, int>::iterator it = m_cdmap->find(p_ad);
	if (it != m_cdmap->end())
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
	if (m_cdmap == nullptr)//no cd yet
	{//create map
		m_cdmap = new std::unordered_map<AbilityDescription*, int>();
	}

	//find target
	std::unordered_map<AbilityDescription*, int>::iterator it = m_cdmap->find(p_ad);
	if (it != m_cdmap->end())
	{//find it and change its cd
		it->second += p_cd;
	}
	else
	{//doesn't find
		if (p_cd > 0)//it is gaining cd
		{
			m_cdmap->insert(std::make_pair(p_ad, p_cd));
		}
	}
}

void unit::CooldownRecorder::reduceCD()
{
	if (m_cdmap == nullptr)//no cd yet
	{
		return;
	}

	for (auto it : *m_cdmap)
	{
		it.second--;//reduce cd by 1
		if (it.second == 0)
		{//remove cd
			m_cdmap->erase(it.first);
		}
	}
}