#pragma once

#include "kitten\mouse picking\ClickableUI.h"
#include "AmbientVolumeController.h"

class DecreaseAmbientVolumeOnClick : public kitten::ClickableUI
{
private:
	int m_amount;
	AmbientVolumeController* m_controller;

	virtual void start() override;
	virtual void onClick() override;
public:
	DecreaseAmbientVolumeOnClick(int p_amount);
	~DecreaseAmbientVolumeOnClick();
};