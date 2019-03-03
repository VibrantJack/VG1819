#pragma once

#include "UI\ClickableButton.h"

class DecreaseResolutionOnClick : public userinterface::ClickableButton
{
private:
	virtual void onClick() override;

public:
	DecreaseResolutionOnClick();
	~DecreaseResolutionOnClick();
};