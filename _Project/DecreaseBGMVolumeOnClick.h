#pragma once

#include "kitten\mouse picking\ClickableUI.h"
#include "BGMVolumeController.h"

class DecreaseBGMVolumeOnClick : public kitten::ClickableUI
{
private:
	int m_amount;
	BGMVolumeController* m_controller;

	virtual void start() override;
	virtual void onClick() override;
public:
	DecreaseBGMVolumeOnClick(int p_amount);
	~DecreaseBGMVolumeOnClick();
};