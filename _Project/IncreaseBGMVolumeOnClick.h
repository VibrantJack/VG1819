#pragma once

#include "UI\ClickableButton.h"

class IncreaseBGMVolumeOnClick : public userinterface::ClickableButton
{
private:
	float m_amount;
	
	virtual void onClick() override;

public:
	IncreaseBGMVolumeOnClick(float p_amount);
	~IncreaseBGMVolumeOnClick();
};