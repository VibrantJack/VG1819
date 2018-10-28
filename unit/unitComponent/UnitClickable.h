#pragma once

#include "kitten\mouse picking\Clickable.h"
#include <string>

//Rock
//This class will handle all click for the unit
//It acts differently based on the situation

namespace unit
{
	class UnitClickable : public kitten::Clickable
	{
	private:
		std::vector<std::string>* m_instructionList;

		std::string m_message;
		bool m_set;

		bool m_show;

		int counter;

		kitten::K_GameObject* m_textBoxGO;

	public:
		UnitClickable();
		virtual ~UnitClickable();

		virtual void onClick() override;
		virtual void onHoverStart() override;
		virtual void onHoverEnd() override;

		void start() override;
		virtual bool hasUpdate() const override { return true; };
		virtual void update() override;

		void setTextBox(kitten::K_GameObject* p_tb);

		void addAbility(const std::string& p_instructionName);
	};
}
