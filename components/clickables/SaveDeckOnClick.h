#pragma once

#include "UI\ClickableButton.h"

class SaveDeckOnClick : public userinterface::ClickableButton
{
private:
public:
	SaveDeckOnClick();
	~SaveDeckOnClick();

	virtual void onClick() override;
};