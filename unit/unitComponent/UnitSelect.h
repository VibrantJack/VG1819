#pragma once

#include "kitten\K_Common.h"
#include "unitAction/ActionButtonStore.h"
#include <string>
#include "kitten\event_system\EventManager.h"

//Rock
//This class will handle all click for the unit
//It acts differently based on the situation

namespace unit
{
	class UnitSelect : public kitten::K_Component
	{
	private:
		ActionButtonStore* m_storage;
		bool m_toggleClickable;
	public:
		UnitSelect();
		virtual ~UnitSelect();

		void start() override;
		void setActionButtonStore(ActionButtonStore* p_s) { m_storage = p_s; };

		void onClick();

		void toggleUnitClickableListener(kitten::Event::EventType p_type, kitten::Event* p_data);
	};
}
