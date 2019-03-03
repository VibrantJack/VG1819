#pragma once

#include "UI\ClickableButton.h"

class DecreaseSFXVolumeOnClick : public userinterface::ClickableButton
{
private:

	float m_amount;
	virtual void onClick() override;

public:
	DecreaseSFXVolumeOnClick(float p_amount);
	~DecreaseSFXVolumeOnClick();
};