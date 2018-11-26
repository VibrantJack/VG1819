#pragma once

#include "kitten\mouse picking\ClickableUI.h"
#include "networking\NetworkingConsoleMenu.h"
#include "_Project\StringInputDisplay.h"
#include "kitten\InputManager.h"
#include "puppy\Text\TextBox.h"

namespace userinterface
{
	class NetworkJoinButton : public kitten::ClickableUI
	{

	public:
		NetworkJoinButton();
		~NetworkJoinButton();

		virtual void start() override;
		virtual bool hasUpdate() const override { return true; };
		virtual void update() override;

		virtual void onClick();

	private:
		NetworkingConsoleMenu* m_menu;
		input::InputManager* m_inputMan;
		puppy::TextBox* m_textBox;
		StringInputDisplay* m_stringInputDisplay;
	};
}