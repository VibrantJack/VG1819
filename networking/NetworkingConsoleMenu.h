#pragma once
#include "kitten\K_Component.h"

class NetworkingConsoleMenu : public kitten::K_Component
{
public:
	NetworkingConsoleMenu();
	~NetworkingConsoleMenu();

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

private:
	bool m_bMenuOpen;
	bool m_bPrintText;

	bool m_bClientUpdate, m_bServerUpdate;
};