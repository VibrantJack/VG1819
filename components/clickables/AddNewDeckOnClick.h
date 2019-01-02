#pragma once

#include "UI\ClickableButton.h"

class AddNewDeckOnClick : public userinterface::ClickableButton
{
private:
public:
	AddNewDeckOnClick();
	~AddNewDeckOnClick();

	virtual void onClick() override;
};