#pragma once

#include "UI\ClickableButton.h"

class IncreaseSFXVolumeOnClick : public userinterface::ClickableButton
{
private:

	float m_amount;

	virtual void onClick() override;

public:
	IncreaseSFXVolumeOnClick(float p_amount);
	~IncreaseSFXVolumeOnClick();

};