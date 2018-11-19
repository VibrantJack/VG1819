#pragma once

#include "kitten\mouse picking\ClickableUI.h"
#include "networking\NetworkingConsoleMenu.h"
#include "_Project\StringInputDisplay.h"
#include "kitten\InputManager.h"

namespace userinterface
{
	class NetworkJoinButton : public kitten::ClickableUI
	{

	public:
		NetworkJoinButton();
		~NetworkJoinButton();

		virtual void start() override;
		virtual void onClick();
	private:
		StringInputDisplay* getStringInputDisplay();

	private:
		NetworkingConsoleMenu* m_menu;
		input::InputManager* m_inputMan;
		StringInputDisplay* m_stringInputDisplay;
	};
}