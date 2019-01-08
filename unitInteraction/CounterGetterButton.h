/*@Rock 1.8
This class handles the behavior of buttons in counter getter.
They are plus, minus, check, cancel.
*/
#pragma once
#include "kitten/mouse picking/ClickableUI.h"

class CounterGetterButton : public kitten::ClickableUI
{
public:
	enum ButtonBehavior
	{
		plus,
		minus,
		check,
		cancel,
	};

	CounterGetterButton(ButtonBehavior p_behavior);
	~CounterGetterButton();

private:

};
