#pragma once

#include "kitten\mouse picking\ClickableUI.h"
#include "SFXVolumeController.h"

class IncreaseSFXVolumeOnClick : public kitten::ClickableUI
{
private:
	int m_amount;
	SFXVolumeController* m_controller;

	virtual void start() override;
	virtual void onClick() override;

public:
	IncreaseSFXVolumeOnClick(int p_amount);
	~IncreaseSFXVolumeOnClick();

};