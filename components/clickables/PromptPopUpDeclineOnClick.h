#pragma once

#include "kitten/mouse picking/ClickableUI.h"

class PromptPopUpDeclineOnClick : public kitten::ClickableUI
{
private:
public:
	PromptPopUpDeclineOnClick(){}
	~PromptPopUpDeclineOnClick(){}

	virtual void onClick() override;
};