#pragma once

#include "UI\ClickableButton.h"
#include "unit\Unit.h"
#include "kitten\InputManager.h"
#include "kitten\event_system\EventManager.h"
#include "kitten\event_system\Event.h"

namespace userinterface
{
	class NextTurnButton : public ClickableButton
	{
	private:
		
	public:
		NextTurnButton();
		~NextTurnButton();

		virtual void onClick();
	};
}