#pragma once

#include "UI\ClickableButton.h"
#include "components/PromptPopUp.h"

class SaveDeckOnClick : public userinterface::ClickableButton, public PromptPopUp::Behavior
{
private:
public:
	SaveDeckOnClick();
	~SaveDeckOnClick();

	void onSuccess() override;
	virtual void onClick() override;
};