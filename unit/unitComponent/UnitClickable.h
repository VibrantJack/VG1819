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
		std::string m_message;
	public:
		UnitClickable();
		virtual ~UnitClickable();

		virtual void onClick() override;
		virtual void onHoverStart() override;
		virtual void onHoverEnd() override;
	};
}
