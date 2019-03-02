#pragma once

#include "UI\ClickableButton.h"

class SavePlayerPrefsOnClick : public userinterface::ClickableButton
{
private:

	virtual void onClick() override;

public:
	SavePlayerPrefsOnClick();
	~SavePlayerPrefsOnClick();
};