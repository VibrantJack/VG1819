#pragma once

#include "kitten\mouse picking\ClickableUI.h"
#include "ResolutionController.h"

class IncreaseResolutionOnClick : public kitten::ClickableUI
{
private:

	ResolutionController* m_resController;

	virtual void start() override;
	virtual void onClick() override;

public:
	IncreaseResolutionOnClick();
	~IncreaseResolutionOnClick();

};