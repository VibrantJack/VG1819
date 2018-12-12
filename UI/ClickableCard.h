#pragma once
#include "kitten\mouse picking\ClickableUI.h"
#include "kitten\event_system\EventManager.h"
#include "kitten\K_GameObject.h"

namespace userinterface
{
	class ContextMenu;

	class ClickableCard : public kitten::ClickableUI
	{
	protected:
		ContextMenu* m_currentContext;
	public:
		ClickableCard();
		~ClickableCard();

		void onHoverStart() override;
		void onHoverEnd() override;

		void toggleEnabledListener(kitten::Event::EventType p_type, kitten::Event* p_data);

		kitten::K_GameObject* m_context;
	};
}
