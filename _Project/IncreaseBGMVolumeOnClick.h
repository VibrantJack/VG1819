#pragma once

#include "kitten\mouse picking\ClickableUI.h"

class IncreaseBGMVolumeOnClick : public kitten::ClickableUI
{
private:
	float m_amount;
	
	virtual void onClick() override;

public:
	IncreaseBGMVolumeOnClick(float p_amount);
	~IncreaseBGMVolumeOnClick();
};