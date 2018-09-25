// Event
// 
// Defines an Event that holds data to be sent through the EventManager
// Stores data in maps in key/value pairs
// Also defines the EventTypes
//
// author: Callum
#include "Event.h"

using namespace kitten;


Event::Event(EventType p_event)
	: m_floatMap(NULL), m_gameObjMap(NULL), m_intMap(NULL), m_stringMap(NULL), m_constGameObjMap(NULL), m_type(p_event)
{

}

Event::~Event()
{
	if (m_floatMap != NULL)
	{
		delete m_floatMap;
	}

	if (m_gameObjMap != NULL)
	{
		delete m_gameObjMap;
	}

	if (m_intMap != NULL)
	{
		delete m_intMap;
	}

	if (m_stringMap != NULL)
	{
		delete m_stringMap;
	}

	if (m_constGameObjMap != NULL)
	{
		delete m_constGameObjMap;
	}
}

void Event::putInt(const std::string& m_key, int m_value)
{
	if (m_intMap == NULL)
	{
		m_intMap = new std::map<std::string, int>();
	}

	m_intMap->insert(std::make_pair(m_key, m_value));
}

void Event::putFloat(const std::string& m_key, float m_value)
{
	if (m_floatMap == NULL)
	{
		m_floatMap = new std::map<std::string, float>();
	}

	m_floatMap->insert(std::make_pair(m_key, m_value));
}

void Event::putString(const std::string& m_key, const std::string& m_value)
{
	if (m_stringMap == NULL)
	{
		m_stringMap = new std::map<std::string, std::string>();
	}

	m_stringMap->insert(std::make_pair(m_key, m_value));
}

void Event::putGameObj(const std::string& m_key, K_GameObject* m_value)
{
	if (m_gameObjMap == NULL)
	{
		m_gameObjMap = new std::map<std::string, K_GameObject*>();
	}

	m_gameObjMap->insert(std::make_pair(m_key, m_value));
}

void Event::putConstGameObj(const std::string& m_key, const K_GameObject* m_value)
{
	if (m_constGameObjMap == NULL)
	{
		m_constGameObjMap = new std::map<std::string, const K_GameObject*>();
	}

	m_constGameObjMap->insert(std::make_pair(m_key, m_value));
}


int Event::getInt(const std::string& m_key)
{
	if (m_intMap == NULL)
	{
		return NULL; //returns 0
	}
	//else

	return m_intMap->at(m_key);
}

float Event::getFloat(const std::string& m_key)
{
	if (m_floatMap == NULL)
	{
		return NULL; //returns 0.0f
	}
	//else

	return m_floatMap->at(m_key);
}

std::string Event::getString(const std::string& m_key)
{
	if (m_stringMap == NULL)
	{
		return NULL;
	}
	//else

	return m_stringMap->at(m_key);
}

K_GameObject* Event::getGameObj(const std::string& m_key)
{
	if (m_gameObjMap == NULL)
	{
		return NULL;
	}
	//else

	return m_gameObjMap->at(m_key);
}

const K_GameObject* Event::getConstGameObj(const std::string& m_key)
{
	if (m_constGameObjMap == NULL)
	{
		return NULL;
	}
	//else

	return m_constGameObjMap->at(m_key);
}