#pragma once

#include "kitten/K_GameObject.h"
#include "Event.h"

#include <map>
#include <vector>
#include <functional>

namespace kitten
{
	class K_Instance;

	class EventManager
	{
		friend class K_Instance;
	private:
		EventManager();
		virtual ~EventManager();
		static EventManager* sm_instance;

		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new EventManager(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };

		std::multimap <Event::EventType,
			std::pair<
			const void*,
			std::function<void(Event::EventType p_type, Event* p_data)>>> m_listeners;
		std::map <Event::EventType, Event*> m_queuedEvents;
		std::vector<std::pair<Event::EventType, const void*>> m_queuedRemovals;

		unsigned int m_eventChain = 0;

		void removeQueuedListeners();
		void update();
		void clear();
	public:
		static EventManager* getInstance() { return sm_instance; };

		void queueEvent(Event::EventType p_type, Event* p_data);
		void triggerEvent(Event::EventType p_type, Event* p_data);
		void addListener(Event::EventType p_type, const void* p_obj, std::function<void(Event::EventType p_type, Event* p_data)> p_listener);
		void removeListener(Event::EventType p_type, const void* p_obj);
		void queueRemoveListener(Event::EventType p_type, const void* p_obj);
	};

}