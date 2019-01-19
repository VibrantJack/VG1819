#pragma once
#include "kitten/mouse picking/ClickableUI.h"
#include "_Project\StringInputDisplay.h"

class StartNewDeckSetupWizard : public kitten::K_Component
{
private:
	StringInputDisplay* m_stringInputDisplay;
public:
	void start();

	StartNewDeckSetupWizard();
	~StartNewDeckSetupWizard();
};