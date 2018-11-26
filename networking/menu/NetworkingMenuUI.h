#pragma once

#include "kitten\K_Component.h"

namespace userinterface
{
	class ClickableUI;

	class NetworkingMenuUI : public kitten::K_Component
	{
		friend class NetworkHostButton;
	public:
		NetworkingMenuUI();
		~NetworkingMenuUI();

		virtual void start() override;
	};
}