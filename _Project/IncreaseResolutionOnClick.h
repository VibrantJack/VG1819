#pragma once

#include "kitten\mouse picking\ClickableUI.h"

class IncreaseResolutionOnClick : public kitten::ClickableUI
{
private:
	float m_amount;
	
	virtual void onClick() override;

public:
	IncreaseResolutionOnClick();
	~IncreaseResolutionOnClick();

};