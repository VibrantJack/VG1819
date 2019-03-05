#pragma once

#include "kitten\mouse picking\ClickableUI.h"

class IncreaseSFXVolumeOnClick : public kitten::ClickableUI
{
private:

	float m_amount;

	virtual void onClick() override;

public:
	IncreaseSFXVolumeOnClick(float p_amount);
	~IncreaseSFXVolumeOnClick();

};