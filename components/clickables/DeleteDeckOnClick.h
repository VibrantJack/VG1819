#pragma once

#include "UI\ClickableButton.h"

class DeleteDeckOnClick : public userinterface::ClickableButton
{
private:
public:
	DeleteDeckOnClick();
	~DeleteDeckOnClick();

	virtual void onClick() override;
};