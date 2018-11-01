#pragma once

#include <unordered_set>
#include "ClickableBox.h"
#include "ClickableFrame.h"
#include "kitten\InputManager.h"

namespace kitten
{
	//@TODO: Sort these based on camera position to make all raycasts faster!!

	class K_Instance;

	class ActiveClickables
	{
		friend class K_Instance;

		friend class input::InputManager;
		friend class ClickableBox;
		friend class ClickableFrame;
	private:
		//Singleton stuff
		ActiveClickables();
		~ActiveClickables();
		static ActiveClickables* sm_instance;

		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new ActiveClickables(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };

		std::unordered_set<ClickableBox*> m_clickables;
		std::unordered_set<ClickableFrame*> m_UIclickables;

		//Jank for deleting thing that the mouse is over..
		ClickableBox* m_lastHover;
		ClickableFrame* m_lastUIHover;

		void addToActive(ClickableBox* p_toAdd);
		void removeFromActive(ClickableBox* p_toRemove);

		void addToActiveUI(ClickableFrame* p_toAdd);
		void removeFromActiveUI(ClickableFrame* p_toRemove);
	public:
		static ActiveClickables* getInstance() { return sm_instance; };

		const std::unordered_set<ClickableBox*>& getClickableList() const;
		const std::unordered_set<ClickableFrame*>& getClickableUIList() const;
	};
}