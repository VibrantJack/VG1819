#pragma once
#include "kitten\K_Component.h"
#include "kitten\event_system\EventManager.h"
#include "_Project\StringInputDisplay.h"
#include "kitten\InputManager.h"

class ConnectToHost : public kitten::K_Component
{
public:
	ConnectToHost();
	~ConnectToHost();

	virtual void start() override;

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

	void joinButtonClickedListener(kitten::Event::EventType p_type, kitten::Event* p_event);
	
	void connect();

private:
	puppy::TextBox* m_textBox;
	StringInputDisplay* m_stringInputDisplay;
	input::InputManager* m_inputMan;

	bool m_bPrintText;
	bool m_bEnteringAddress;
};
