#pragma once

#include "UI\ClickableButton.h"

class ExitGameButton : public userinterface::ClickableButton
{

public:
	ExitGameButton();
	~ExitGameButton();

	virtual void onClick() override;
};