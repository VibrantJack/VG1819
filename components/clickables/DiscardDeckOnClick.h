#pragma once

#include "UI\ClickableButton.h"

class DiscardDeckOnClick : public userinterface::ClickableButton
{
private:
public:
	DiscardDeckOnClick();
	~DiscardDeckOnClick();

	virtual void onClick() override;
};