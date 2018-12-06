#pragma once
#include "kitten\mouse picking\ClickableUI.h"
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

		kitten::K_GameObject* m_context;
	};
}
