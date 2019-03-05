#pragma once

#include "kitten\mouse picking\ClickableUI.h"

class SavePlayerPrefsOnClick : public kitten::ClickableUI
{
private:

	virtual void onClick() override;

public:
	SavePlayerPrefsOnClick();
	~SavePlayerPrefsOnClick();
};