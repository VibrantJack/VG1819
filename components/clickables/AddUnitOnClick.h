#pragma once

#include "UI\ClickableButton.h"

class AddUnitOnClick : public userinterface::ClickableButton
{
private:
public:
	AddUnitOnClick();
	~AddUnitOnClick();

	virtual void onClick() override;
};