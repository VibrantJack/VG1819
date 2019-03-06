#pragma once

#include "kitten\mouse picking\ClickableUI.h"
#include "BGMVolumeController.h"

class IncreaseBGMVolumeOnClick : public kitten::ClickableUI
{
private:
	int m_amount;
	BGMVolumeController* m_controller;

	virtual void start() override;
	virtual void onClick() override;
public:
	IncreaseBGMVolumeOnClick(int p_amount);
	~IncreaseBGMVolumeOnClick();
};