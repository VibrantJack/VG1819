#include "CastTimer.h"

unit::CastTimer::CastTimer()
{
	m_cast = false;
	m_pack = nullptr;
}

unit::CastTimer::~CastTimer()
{
	if (m_pack != nullptr)
	{
		delete m_pack;
	}
}

bool unit::CastTimer::isCasting()
{
	return m_cast;
}

std::vector<kitten::K_GameObject*> unit::CastTimer::getTarget()
{
	return m_pack->m_targetTilesGO;
}

void unit::CastTimer::set(std::string p_abilityName, ability::AbilityInfoPackage * p_pack, int p_timer)
{
	m_abilityName = p_abilityName;
	m_pack = p_pack;
	m_timer = p_timer;
	m_cast = true;
}

void unit::CastTimer::changeTimer(int p_n)
{
	if (!m_cast)
		return;

	m_timer += p_n;
	if (m_timer <= 0)
	{
		cast();
		m_cast = false;
	}
}

void unit::CastTimer::cancelCast()
{
	if (m_cast)
	{
		delete m_pack;
		m_pack = nullptr;
		m_cast = false;
	}
}

void unit::CastTimer::cast()
{
	ability::AbilityManager::getInstance()->useAbility(m_abilityName, m_pack);
	m_pack = nullptr;
}
