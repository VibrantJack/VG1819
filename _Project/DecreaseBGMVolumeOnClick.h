#pragma once

#include "UI\ClickableButton.h"

class DecreaseBGMVolumeOnClick : public userinterface::ClickableButton
{
private:
	float m_amount;

	virtual void onClick() override;

public:
	DecreaseBGMVolumeOnClick(float p_amount);
	~DecreaseBGMVolumeOnClick();


};