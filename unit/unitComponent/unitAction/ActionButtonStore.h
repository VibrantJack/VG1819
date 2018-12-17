/*@Rock
This class store a list of action button.
It will create new button if not enough.
It also display a list of button on screen.
Button behaviors are depends on unit.
Position is depend on mouse position.
*/

#pragma once
#include "unit/Unit.h"
#include "ActionSelect.h"

namespace unit
{
	class ActionButtonStore
	{
	public:
		ActionButtonStore();
		~ActionButtonStore();

		void display(Unit* p_u);
		void hide();

	private:
		std::vector<kitten::K_GameObject*> m_buttonList;

		int m_lastX;
		int m_lastY;
		int m_index;
		Unit* m_unit;
	
		void createNewButton();
		void setButton(const std::string& p_msg);
	};
}