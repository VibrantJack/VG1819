#pragma once
#include "kitten\K_Component.h"
#include "_Project\StringInputDisplay.h"
#include "kitten\InputManager.h"
#include "kitten\event_system\EventManager.h"

class NetworkingConsoleMenu : public kitten::K_Component
{
public:
	NetworkingConsoleMenu();
	~NetworkingConsoleMenu();

	virtual void start() override;

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

	void hostGame();
	void stopHosting();

	void connectToHost(const std::string& p_strAddress = "127.0.0.1");
	void disconnectFromHost(bool p_bServerShutdown = false);

	bool checkClientNetwork();
	bool checkServerNetwork();

	void joinButtonClickedListener(kitten::Event::EventType p_type, kitten::Event* p_event);
	void hostButtonClickedListener(kitten::Event::EventType p_type, kitten::Event* p_event);

	void setMenuKeys(
		char p_cEnterMenuKey, char p_cExitMenuKey,
		char p_cHostKey, char p_cStopHostKey,	
		char p_cConnectKey,	char p_cDisconnectKey		
	);

private:
	puppy::TextBox* m_textBox;
	StringInputDisplay* m_stringInputDisplay;
	input::InputManager* m_inputMan;

	bool m_bMenuOpen;
	bool m_bPrintText;
	bool m_bEnteringAddress;
	bool m_bClientUpdate, m_bServerUpdate;

	char m_cEnterMenuKey = '`';
	char m_cHostKey = '5';
	char m_cStopHostKey = '6';
	char m_cConnectKey = '7';
	char m_cDisconnectKey = '8';
	char m_cExitMenuKey = '9';
};

void serverLoop(void* arg);