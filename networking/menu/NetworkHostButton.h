#pragma once

#include "kitten\mouse picking\ClickableUI.h"
#include "networking\NetworkingConsoleMenu.h"
#include "puppy\Text\TextBox.h"

namespace userinterface
{

	class NetworkHostButton : public kitten::ClickableUI
	{

	public:
		NetworkHostButton();
		~NetworkHostButton();

		virtual void start() override;
		virtual void onClick();

	private:
		NetworkingConsoleMenu* m_menu;
		puppy::TextBox* m_textBox;
	};

}