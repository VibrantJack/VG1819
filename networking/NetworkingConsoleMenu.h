#pragma once
#include "kitten\K_Component.h"

class NetworkingConsoleMenu : public kitten::K_Component
{
public:
	NetworkingConsoleMenu();
	~NetworkingConsoleMenu();

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

	void hostGame();
	void stopHosting();
	void connectToHost(const std::string& p_strAddr = "127.0.0.1");
	void disconnectFromHost(bool p_bServerShutdown = false);

	bool checkClientNetwork();
	bool checkServerNetwork();
	void setMenuKeys(
		char p_cEnterMenuKey, char p_cExitMenuKey,
		char p_cHostKey, char p_cStopHostKey,	
		char p_cConnectKey,	char p_cDisconnectKey		
	);

private:
	bool m_bMenuOpen;
	bool m_bPrintText;

	bool m_bClientUpdate, m_bServerUpdate;

	char m_cEnterMenuKey = '`';
	char m_cHostKey = '5';
	char m_cStopHostKey = '6';
	char m_cConnectKey = '7';
	char m_cDisconnectKey = '8';
	char m_cExitMenuKey = '9';
};

void serverLoop(void* arg);