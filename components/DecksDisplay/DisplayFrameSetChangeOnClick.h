#pragma once
#include "kitten/mouse picking/ClickableUI.h"
#include "components/DisplayFrame.h"

class DisplayFrameSetChangeOnClick : public kitten::ClickableUI
{
private:
	const int m_offset;
	DisplayFrame* m_parent;
public:
	void onClick();
	void setParentDisplayFrame(DisplayFrame* p_parent) { m_parent = p_parent; }

	DisplayFrameSetChangeOnClick(const int p_offset) : m_offset(p_offset) {}
	~DisplayFrameSetChangeOnClick() {}
};