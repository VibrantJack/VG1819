#pragma once
#include "kitten\mouse picking\ClickableUI.h"
#include "kitten\K_GameObject.h"
#include "puppy\Text\FontTable.h"
#include "puppy\Text\Font.h"
#include "puppy\Text\TextBox.h"
#include "puppy\Text\TextTable.h"


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
