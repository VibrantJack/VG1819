#include "UI\GameplayButtons\NextTurnButton.h"

namespace userinterface
{
	NextTurnButton::NextTurnButton()
	{

	}

	NextTurnButton::~NextTurnButton()
	{

	}

	void NextTurnButton::onClick()
	{
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::New_Unit_Turn, new kitten::Event(kitten::Event::New_Unit_Turn));
	}
}