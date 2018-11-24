#pragma once

#include "kitten\mouse picking\ClickableUI.h"
#include "networking\NetworkingConsoleMenu.h"

namespace userinterface
{

	class ReturnToMainMenuButton : public kitten::ClickableUI
	{

	public:
		ReturnToMainMenuButton();
		~ReturnToMainMenuButton();

		virtual void onDisabled() override;
		virtual void onEnabled() override;

		virtual void start() override;
		virtual void onClick();

	private:
		NetworkingConsoleMenu* m_menu;
	};

}