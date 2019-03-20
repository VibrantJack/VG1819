#pragma once
#include "kitten\K_Component.h"
#include "kitten\event_system\EventManager.h"
#include "_Project\StringInputDisplay.h"
#include "kitten\InputManager.h"

class ConnectToHost : public kitten::K_Component
{
private:
	puppy::TextBox* m_ipInputTextBox;
	puppy::TextBox* m_localHostTextBox;
	StringInputDisplay* m_stringInputDisplay;
	input::InputManager* m_inputMan;
	kitten::K_GameObject* m_loadingMessage;

	bool m_bConnect;
	bool m_bLoadingMsgEnabled;
	bool m_bJoiningGame;
public:
	ConnectToHost();
	~ConnectToHost();

	virtual void start() override;

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;
	
	void joinDirectAddress();
	void pollForLocalhost();
	void joinLocalhost();
	void joinDedicatedServer();

	void joinDirectAddressListener(kitten::Event::EventType p_type, kitten::Event* p_event);
	void pollForLocalhostListener(kitten::Event::EventType p_type, kitten::Event* p_event);
	void joinLocalhostListener(kitten::Event::EventType p_type, kitten::Event* p_event);
	void quickplayListener(kitten::Event::EventType p_type, kitten::Event* p_event);
	void lostConnectionListener(kitten::Event::EventType p_type, kitten::Event* p_event);
};
