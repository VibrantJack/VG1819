#pragma once

#include "UI\ClickableButton.h"

namespace userinterface
{
	class NetworkJoinButton : public ClickableButton
	{

	public:
		NetworkJoinButton();
		~NetworkJoinButton();

		virtual void onClick();
	};
}