#pragma once

#include <list>
#include "Clickable.h"

namespace kitten
{
	//@TODO: Sort these based on camera position to make all raycasts faster!!

	class ActiveClickables
	{
	private:
		//Singleton stuff
		static ActiveClickables* sm_instance;

		std::list<Clickable*> m_clickables;
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