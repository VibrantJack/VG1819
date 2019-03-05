#pragma once

#include "kitten\mouse picking\ClickableUI.h"

#include "ResolutionController.h"

class DecreaseResolutionOnClick : public kitten::ClickableUI
{
private:

	ResolutionController* m_resController;

	virtual void start() override;
	virtual void onClick() override;

public:
	DecreaseResolutionOnClick();
	~DecreaseResolutionOnClick();
};