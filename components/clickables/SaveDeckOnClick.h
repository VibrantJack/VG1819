#pragma once

#include "UI\ClickableButton.h"
#include "kitten/K_GameObject.h"

class SaveDeckOnClick : public userinterface::ClickableButton
{
private:
	kitten::K_GameObject* m_message = nullptr;
public:
	SaveDeckOnClick();
	~SaveDeckOnClick();

	virtual void onClick() override;
};