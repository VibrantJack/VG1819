#pragma once
#include "kitten/mouse picking/ClickableUI.h"

class DecksDisplaySetChangeOnClick : public kitten::ClickableUI
{
private:
	const int m_offset;
public:
	void onClick();

	DecksDisplaySetChangeOnClick(const int& p_offset) : m_offset(p_offset) {}
	~DecksDisplaySetChangeOnClick() {}
};