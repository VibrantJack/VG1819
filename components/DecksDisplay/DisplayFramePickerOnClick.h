#pragma once
#include "kitten/mouse picking/ClickableUI.h"
#include "components/DisplayFrame.h"

class DisplayFramePickerOnClick : public kitten::ClickableUI
{
private:
	DisplayFrame* m_parent;
public:
	void onClick();
	void setParentDisplayFrame(DisplayFrame* p_parent) { m_parent = p_parent; }

	DisplayFramePickerOnClick() {}
	~DisplayFramePickerOnClick() {}
};