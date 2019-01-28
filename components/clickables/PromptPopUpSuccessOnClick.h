#pragma once

#include "kitten/mouse picking/ClickableUI.h"

class PromptPopUpSuccessOnClick : public kitten::ClickableUI
{
private:
public:
	PromptPopUpSuccessOnClick(){}
	~PromptPopUpSuccessOnClick(){}

	virtual void onClick() override;
};