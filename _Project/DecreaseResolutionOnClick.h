#pragma once

#include "kitten\mouse picking\ClickableUI.h"

class DecreaseResolutionOnClick : public kitten::ClickableUI
{
private:
	virtual void onClick() override;

public:
	DecreaseResolutionOnClick();
	~DecreaseResolutionOnClick();
};