#pragma once

#include "kitten\mouse picking\ClickableUI.h"
#include "AmbientVolumeController.h"

// I should have combined these and DecreaseXXX as well..
class IncreaseAmbientVolumeOnClick : public kitten::ClickableUI
{
private:
	int m_amount;
	AmbientVolumeController* m_controller;

	virtual void start() override;
	virtual void onClick() override;
public:
	IncreaseAmbientVolumeOnClick(int p_amount);
	~IncreaseAmbientVolumeOnClick();
};