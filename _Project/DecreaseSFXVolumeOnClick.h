#pragma once
#include "kitten\mouse picking\ClickableUI.h"

class DecreaseSFXVolumeOnClick : public kitten::ClickableUI
{
private:

	float m_amount;
	virtual void onClick() override;

public:
	DecreaseSFXVolumeOnClick(float p_amount);
	~DecreaseSFXVolumeOnClick();
};