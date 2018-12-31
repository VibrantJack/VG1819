#pragma once

#include "UI\ClickableButton.h"
#include "kitten\InputManager.h"

namespace userinterface
{
	class NetworkConnectButton : public ClickableButton
	{
	private:
		kitten::K_GameObject* m_ipBox;
		input::InputManager* m_inputMan;
	public:
		NetworkConnectButton();
		~NetworkConnectButton();

		virtual void start() override;
		virtual void onClick();
	};
}