#pragma once
#include "kitten/mouse picking/ClickableUI.h"

class DecksDisplayPickerOnClick : public kitten::ClickableUI
{
private:

public:
	void onClick();

	DecksDisplayPickerOnClick() {}
	~DecksDisplayPickerOnClick() {}
};