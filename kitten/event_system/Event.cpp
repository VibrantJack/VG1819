// Event
// 
// Defines an Event that holds data to be sent through the EventManager
// Stores data in maps in key/value pairs
// Also defines the EventTypes
//
// author: Callum
#include "Event.h"

namespace kitten
{

	Event::Event(EventType p_event)
		: m_floatMap(nullptr), m_gameObjMap(nullptr), m_intMap(nullptr), m_stringMap(nullptr), m_constGameObjMap(nullptr), m_type(p_event)
	{

	}

	Event::~Event()
	{
		if (m_floatMap != nullptr)
		{
			delete m_floatMap;
		}

		if (m_gameObjMap != nullptr)
		{
			delete m_gameObjMap;
		}

		if (m_intMap != nullptr)
		{
			delete m_intMap;
		}

		if (m_stringMap != nullptr)
		{
			delete m_stringMap;
		}

		if (m_constGameObjMap != nullptr)
		{
			delete m_constGameObjMap;
		}
	}

	void Event::putInt(const std::string& p_key, int m_value)
	{
		if (m_intMap == nullptr)
		{
			m_intMap = new std::unordered_map<std::string, int>();
		}

		m_intMap->insert(std::make_pair(p_key, m_value));
	}

	void Event::putFloat(const std::string& p_key, float m_value)
	{
		if (m_floatMap == nullptr)
		{
			m_floatMap = new std::unordered_map<std::string, float>();
		}

		m_floatMap->insert(std::make_pair(p_key, m_value));
	}

	void Event::putString(const std::string& p_key, const std::string& m_value)
	{
		if (m_stringMap == nullptr)
		{
			m_stringMap = new std::unordered_map<std::string, std::string>();
		}

		m_stringMap->insert(std::make_pair(p_key, m_value));
	}

	void Event::putGameObj(const std::string& p_key, K_GameObject* m_value)
	{
		if (m_gameObjMap == nullptr)
		{
			m_gameObjMap = new std::unordered_map<std::string, K_GameObject*>();
		}

		m_gameObjMap->insert(std::make_pair(p_key, m_value));
	}

	void Event::putConstGameObj(const std::string& p_key, const K_GameObject* m_value)
	{
		if (m_constGameObjMap == nullptr)
		{
			m_constGameObjMap = new std::unordered_map<std::string, const K_GameObject*>();
		}

		m_constGameObjMap->insert(std::make_pair(p_key, m_value));
	}


	int Event::getInt(const std::string& p_key)
	{
		if (m_intMap == nullptr)
		{
			assert(false);
			return 0; //returns 0
		}
		//else

		return m_intMap->at(p_key);
	}

	float Event::getFloat(const std::string& p_key)
	{
		if (m_floatMap == nullptr)
		{
			assert(false);
			return 0.0f; //returns 0.0f
		}
		//else

		return m_floatMap->at(p_key);
	}

	std::string Event::getString(const std::string& p_key)
	{
		if (m_stringMap == nullptr)
		{
			return nullptr;
		}
		//else

		return m_stringMap->at(p_key);
	}

	K_GameObject* Event::getGameObj(const std::string& p_key)
	{
		if (m_gameObjMap == nullptr)
		{
			return nullptr;
		}
		//else

		return m_gameObjMap->at(p_key);
	}

	const K_GameObject* Event::getConstGameObj(const std::string& p_key)
	{
		if (m_constGameObjMap == nullptr)
		{
			return nullptr;
		}
		//else

		return m_constGameObjMap->at(p_key);
	}
}