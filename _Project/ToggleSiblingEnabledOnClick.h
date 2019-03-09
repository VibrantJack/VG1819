#pragma once
#include "kitten\mouse picking\ClickableUI.h"

class ToggleSiblingEnabledOnClick : public kitten::ClickableUI
{
private:
	kitten::K_GameObject* m_sibling;

	virtual void start() override;
	virtual void onClick() override;
public:
	ToggleSiblingEnabledOnClick();
	~ToggleSiblingEnabledOnClick();
};