/*@Rock
This class store a list of action button.
It will create new button if not enough.
It also display a list of button on screen.
Button behaviors are depends on unit.
Position is depend on mouse position.
*/

#pragma once
#include "ActionSelect.h"

namespace unit
{
	class Unit;
	class ActionButtonStore
	{
	public:
		ActionButtonStore();
		~ActionButtonStore();

		void display(Unit* p_u);
		void displayAction(kitten::K_GameObject* p_buttonGO);
		void hide();
		void hideAction();

		void listenEvent(kitten::Event::EventType p_type, kitten::Event* p_event);
	private:
		ActionMap* m_map;

		std::vector<kitten::K_GameObject*> m_buttonList;

		Unit* m_unit;

		//window size
		int m_winX;
		int m_winY;
		int m_centerX;
		int m_centerY;

		//pos for last button
		int m_lastX;
		int m_lastY;

		//button scale
		int m_buttonScaleX;
		int m_buttonScaleY;

		//index of button in vector
		int m_index;
		int m_actionStartIndex;
		int m_actionEndIndex;

		//flag of displaying buttons
		bool m_show;
		bool m_actionShow;

		//flag of moveing buttons
		bool m_xChange;



		void createNewButton();

		void setButton(const std::string& p_msg, bool p_a, int p_cd = 0);

		void getButtonScale();

		void setAbility();

		void registerEvent();
		void deregisterEvent();
	};
}