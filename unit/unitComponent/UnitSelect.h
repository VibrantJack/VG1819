#pragma once

#include "kitten\K_Common.h"
#include <string>

//Rock
//This class will handle all click for the unit
//It acts differently based on the situation

namespace unit
{
	class UnitSelect : public kitten::K_Component
	{
	private:
		std::vector<std::string>* m_instructionList;

		std::string m_message;
		bool m_set;

		bool m_select;

		int counter;

		kitten::K_GameObject* m_textBoxGO;

	public:
		UnitSelect();
		virtual ~UnitSelect();

		void start() override;
		void setTextBox(kitten::K_GameObject* p_tb);

		void addAbility(const std::string& p_instructionName);
	};
}
