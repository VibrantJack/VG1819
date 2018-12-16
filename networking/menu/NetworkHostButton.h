#pragma once

#include "UI\ClickableButton.h"

namespace userinterface
{

	class NetworkHostButton : public ClickableButton
	{

	public:
		NetworkHostButton();
		~NetworkHostButton();

		virtual void onClick();
	};

}