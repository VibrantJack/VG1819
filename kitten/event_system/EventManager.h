#pragma once

#include "kitten/K_GameObject.h"
#include "Event.h"

#include <map>
#include <vector>
#include <functional>

namespace kitten
{
	class EventManager
	{
	private:
		EventManager();
		virtual ~EventManager();
		static EventManager* sm_instance;

		std::multimap <Event::EventType,
			std::pair<
			void*,
			std::function<void(Event::EventType p_type, Event* p_data)>>> m_listeners;
		std::map <Event::EventType, Event*> m_queuedEvents;		

	public:
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new EventManager(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
		static EventManager* getInstance() { return sm_instance; };

		void queueEvent(Event::EventType p_type, Event* p_data);
		void triggerEvent(Event::EventType p_type, Event* p_data);
		void addListener(Event::EventType p_type, void* p_obj, std::function<void(Event::EventType p_type, Event* p_data)> p_listener);
		void removeListener(Event::EventType p_type, void* p_obj);

		void clear();

		void update();
	};

} // namespace kitten