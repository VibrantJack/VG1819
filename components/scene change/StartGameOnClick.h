#pragma once
#include "kitten/mouse picking/ClickableUI.h"

class StartGameOnClick : public kitten::ClickableUI
{
private:
public:
	void onClick();

	StartGameOnClick() {}
	~StartGameOnClick() {}
};