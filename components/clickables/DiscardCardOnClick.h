#pragma once
#include "kitten/mouse picking/ClickableUI.h"
#include "_Project/LerpController.h"


class DiscardCardOnClick : public kitten::ClickableUI, LerpController::PositionLerpFinishedCallback
{
protected:
	LerpController* m_lerpController = nullptr;

	void onPositionLerpFinished() override;
public:
	DiscardCardOnClick(bool p_backToOrigin = false);
	~DiscardCardOnClick();

	void start() override;
	void onClick() override;
};
