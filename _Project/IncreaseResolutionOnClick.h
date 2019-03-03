#pragma once

#include "UI\ClickableButton.h"

class IncreaseResolutionOnClick : public userinterface::ClickableButton
{
private:
	float m_amount;
	
	virtual void onClick() override;

public:
	IncreaseResolutionOnClick();
	~IncreaseResolutionOnClick();

};