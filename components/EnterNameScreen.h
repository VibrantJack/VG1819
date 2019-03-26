#pragma once
#include "kitten\K_Component.h"
#include "_Project\StringInputDisplay.h"
#include "UI\ClickableButton.h"
#include "kitten\mouse picking\ClickableFrame.h"

class EnterNameScreen : public kitten::K_Component
{
private:
	puppy::TextBox* m_inputTextbox;
	puppy::TextBox* m_nameStatusTextBox;
	StringInputDisplay* m_stringInputDisplay;
	userinterface::ClickableButton* m_confirmButton;
	kitten::ClickableFrame* m_confirmButtonFrame;

	int m_nameMaxLimit;
	int m_nameMinLimit;

	virtual void start() override;

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

	void sceneChangeListener(kitten::Event::EventType p_type, kitten::Event* p_event);
	void setClientPlayerName();
	void setConfirmButtonEnabled(bool p_enabled);
public:
	EnterNameScreen(int p_nameMinLimit, int p_nameMaxLimit);
	~EnterNameScreen();
};
