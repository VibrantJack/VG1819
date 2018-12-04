#pragma once

#include "kitten\mouse picking\ClickableUI.h"

namespace userinterface
{

	class NetworkHostButton : public kitten::ClickableUI
	{

	public:
		NetworkHostButton();
		~NetworkHostButton();

		virtual void onClick();
	};

}