/*
@Rock
This class handles the action that the button will perform
basically same as SelectAbility
*/

#pragma once

#include "kitten/mouse picking/ClickableUI.h"
#include "puppy\Text\TextBox.h"
#include "unit/Unit.h"

namespace unit
{
	class ActionButtonStore;
	class ActionSelect : public kitten::ClickableUI
	{
	private:
		const int m_offsetX = 15;
		const int m_offsetY = 32;

		std::string m_action;
		Unit* m_unit;
		kitten::K_GameObject* m_text;
		ActionButtonStore* m_storage;
	public:
		ActionSelect();
		~ActionSelect();

		void start() override;

		void setStorage(ActionButtonStore* p_s) {m_storage = p_s;};
		void setUnit(Unit* p_u);
		void setAction(const std::string& p_a);
		const std::string getAction() { return m_action; };

		void act();

		void onClick() override;

		void onDisabled() override;
	};
}
