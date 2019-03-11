#pragma once

#include "kitten\mouse picking\ClickableUI.h"
#include "SFXVolumeController.h"

class DecreaseSFXVolumeOnClick : public kitten::ClickableUI
{
private:
	int m_amount;
	SFXVolumeController* m_controller;

	virtual void start() override;
	virtual void onClick() override;

public:
	DecreaseSFXVolumeOnClick(int p_amount);
	~DecreaseSFXVolumeOnClick();
};