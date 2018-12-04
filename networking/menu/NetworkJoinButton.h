#pragma once

#include "kitten\mouse picking\ClickableUI.h"
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
		kitten::K_GameObject* m_ipBox;
		input::InputManager* m_inputMan;
	};
}