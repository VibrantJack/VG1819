#pragma once

#include "UI\ClickableButton.h"
#include "components/PromptPopUp.h"

class DeleteDeckOnClick : public userinterface::ClickableButton, PromptPopUp::Behavior
{
private:
	kitten::K_GameObject* m_message = nullptr;
public:
	DeleteDeckOnClick();
	~DeleteDeckOnClick();
	virtual void onSuccess() override;

	virtual void onClick() override;
};