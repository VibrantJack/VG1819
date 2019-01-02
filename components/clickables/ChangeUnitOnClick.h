#pragma once

#include "UI\ClickableButton.h"

class ChangeUnitOnClick : public userinterface::ClickableButton
{
private:
	bool m_increment = true;
public:
	ChangeUnitOnClick(bool p_increment);
	~ChangeUnitOnClick();

	virtual void onClick() override;
};