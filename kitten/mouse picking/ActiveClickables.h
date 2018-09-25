#pragma once

#include <list>
#include "Clickable.h"
#include "kitten\InputManager.h"

namespace kitten
{
	//@TODO: Sort these based on camera position to make all raycasts faster!!

	class ActiveClickables
	{
		friend class input::InputManager;
	private:
		//Singleton stuff
		static ActiveClickables* sm_instance;

		std::list<Clickable*> m_clickables;

		//Jank for deleting thing that the mouse is over..
		Clickable* m_lastHover;
	public:
		//Singleton stuff
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new ActiveClickables(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
		static ActiveClickables* getInstance() { return sm_instance; };

		void addToActive(Clickable* p_toAdd);
		void removeFromActive(Clickable* p_toRemove);
		const std::list<Clickable*>& getClickableList() const;

		
	};
}