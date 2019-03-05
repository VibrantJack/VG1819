#pragma once

#include "kitten\mouse picking\ClickableUI.h"

class DisableParentOnClick : public kitten::ClickableUI
{
private:
	
	virtual void onClick() override;

public:
	DisableParentOnClick();
	~DisableParentOnClick();
};