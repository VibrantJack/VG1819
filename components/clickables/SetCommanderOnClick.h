#pragma once

#include "UI\ClickableButton.h"

class SetCommanderOnClick : public userinterface::ClickableButton
{
private:
public:
	SetCommanderOnClick();
	~SetCommanderOnClick();

	virtual void onClick() override;
};