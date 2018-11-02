#include "TimePointEvent.h"

ability::TimePointEvent::TimePointEvent(TPEventType p_event)
	: m_intMap(nullptr),m_packageMap(nullptr),m_gameObjMap(nullptr)
{
	m_type = p_event;
}

ability::TimePointEvent::~TimePointEvent()
{
	if (m_intMap != nullptr)
	{
		delete m_intMap;
	}
	if (m_gameObjMap != nullptr)
	{
		delete m_gameObjMap;
	}
	if (m_packageMap != nullptr)
	{
		delete m_packageMap;
	}
}

void ability::TimePointEvent::putInt(const std::string & p_key, int p_value)
{
	if (m_intMap == nullptr)
	{
		m_intMap = new std::unordered_map<std::string, int>();
	}

	m_intMap->insert(std::make_pair(p_key, p_value));
}

void ability::TimePointEvent::putPackage(const std::string & p_key, ability::AbilityInfoPackage * p_pack)
{
	if (m_packageMap == nullptr)
	{
		m_packageMap = new std::unordered_map<std::string, ability::AbilityInfoPackage *>();
	}

	m_packageMap->insert(std::make_pair(p_key, p_pack));
}

void ability::TimePointEvent::putGameObject(const std::string & p_key, kitten::K_GameObject * p_value)
{
	if (m_gameObjMap == nullptr)
	{
		m_gameObjMap = new std::unordered_map<std::string, kitten::K_GameObject *>();
	}

	m_gameObjMap->insert(std::make_pair(p_key, p_value));
}

int ability::TimePointEvent::getInt(const std::string & p_key)
{
	if (m_intMap == nullptr)
	{
		assert(false);
		return 0; //returns 0
	}
	//else

	return m_intMap->at(p_key);
}

ability::AbilityInfoPackage * ability::TimePointEvent::getPackage(const std::string & p_key)
{
	if (m_packageMap == nullptr)
	{
		assert(false);
		return 0; //returns 0
	}
	//else

	return m_packageMap->at(p_key);
}

kitten::K_GameObject * ability::TimePointEvent::getGameObject(const std::string & p_key)
{
	if (m_gameObjMap == nullptr)
	{
		assert(false);
		return 0; //returns 0
	}
	//else

	return m_gameObjMap->at(p_key);
}
