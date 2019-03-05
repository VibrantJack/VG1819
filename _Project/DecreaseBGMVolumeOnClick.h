#pragma once

#include "kitten\mouse picking\ClickableUI.h"

class DecreaseBGMVolumeOnClick : public kitten::ClickableUI
{
private:
	float m_amount;

	virtual void onClick() override;

public:
	DecreaseBGMVolumeOnClick(float p_amount);
	~DecreaseBGMVolumeOnClick();


};