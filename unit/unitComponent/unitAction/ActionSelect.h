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
		const float m_textZ = 0.1;
		const std::pair<int, int> m_txtOffset;
		const std::pair<int,int> m_cdOffset;

		int m_cd;
		std::string m_action;

		Unit* m_unit;

		kitten::K_GameObject* m_text;
		kitten::K_GameObject* m_cdtext;

		ActionButtonStore* m_storage;
	public:
		ActionSelect(const std::pair<int,int> p_to, const std::pair<int, int> p_co);
		~ActionSelect();

		void start() override;

		void setStorage(ActionButtonStore* p_s) {m_storage = p_s;};
		void setUnit(Unit* p_u);
		void setAction(const std::string& p_a, int p_cd = 0);
		const std::string getAction() { return m_action; };

		void act();

		void onClick() override;

		void onDisabled() override;
	};
}
