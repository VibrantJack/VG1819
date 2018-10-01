// EventManager
//
// Singleton: use getInstance() to call methods
// Add/remove listeners by providing an EventType, a reference to the class of the method
//	to be called, and the function itself through std::bind
// Trigger events immediately or queue them to be called during update()
//
// Built using Callum's existing event system from CS4650
// author: Callum
#include "EventManager.h"

namespace kitten
{

	// Static singleton instance
	EventManager* EventManager::sm_instance = NULL;

	EventManager::EventManager()
	{

	}

	EventManager::~EventManager()
	{

	}

	void EventManager::queueEvent(Event::EventType p_type, Event* p_data)
	{
		m_queuedEvents.insert(std::pair<Event::EventType, Event*>(p_type, p_data));
	}

	void EventManager::triggerEvent(Event::EventType p_type, Event* p_data)
	{
		auto range = m_listeners.equal_range(p_type);

		for (auto it = range.first; it != range.second; ++it)
		{
			//it->pair.func
			it->second.second(p_type, p_data);
		}

		delete p_data;
	}

	void EventManager::addListener(Event::EventType p_type, void* p_ptr, std::function<void(Event::EventType, Event*)> p_listener)
	{
		m_listeners.insert(std::make_pair(p_type, std::make_pair(p_ptr, p_listener)));
	}

	void EventManager::removeListener(Event::EventType p_type, void* p_ptr)
	{
		auto it = m_listeners.begin();
		for (it; it != m_listeners.end(); ++it)
		{
			if ((*it).first == p_type && it->second.first == p_ptr)
			{
				m_listeners.erase(it);
				return;
			}
		}
	}

	void EventManager::update()
	{
		//Trigger queued events
		for (auto it = m_queuedEvents.begin(); it != m_queuedEvents.end(); ++it)
		{
			//notify listeners of type (first) of event (second)
			auto range = m_listeners.equal_range(it->first);
			for (auto mapIt = range.first; mapIt != range.second; ++mapIt)
			{
				//it->pair.func
				mapIt->second.second(it->first, it->second);
			}

			delete it->second;
		}

		m_queuedEvents.clear();
	}


	void EventManager::clear()
	{
		m_listeners.clear();
		m_queuedEvents.clear();
	}
}