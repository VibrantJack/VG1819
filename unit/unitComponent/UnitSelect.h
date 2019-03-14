#pragma once

#include "kitten\K_Common.h"
#include <string>

//Rock
//This class will handle all click for the unit
//It acts differently based on the situation

namespace unit
{
	class ActionButtonStore;
	class UnitSelect : public kitten::K_Component
	{
	private:
		ActionButtonStore* m_storage;
		bool m_disableInteraction;
	public:
		UnitSelect();
		virtual ~UnitSelect();

		void start() override;

		void setActionButtonStore(ActionButtonStore* p_s) { m_storage = p_s; }; 
		ActionButtonStore* getButtonStorage() { return m_storage; };

		void disableInteraction(bool p_disable);

		void onClick();
	};
}
