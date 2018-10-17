#pragma once

#include <list>
#include "ClickableBox.h"
#include "ClickableFrame.h"
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

		std::list<ClickableBox*> m_clickables;
		std::list<ClickableFrame*> m_UIclickables;

		//Jank for deleting thing that the mouse is over..
		ClickableBox* m_lastHover;
		ClickableFrame* m_lastUIHover;
	public:
		//Singleton stuff
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new ActiveClickables(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
		static ActiveClickables* getInstance() { return sm_instance; };

		void addToActive(ClickableBox* p_toAdd);
		void removeFromActive(ClickableBox* p_toRemove);
		const std::list<ClickableBox*>& getClickableList() const;

		void addToActiveUI(ClickableFrame* p_toAdd);
		void removeFromActiveUI(ClickableFrame* p_toRemove);
		const std::list<ClickableFrame*>& getClickableUIList() const;

	};
}