#pragma once
#include "kitten\K_Component.h"
#include "kitten\event_system\EventManager.h"
#include "_Project\StringInputDisplay.h"
#include "kitten\InputManager.h"
#include "kitten\mouse picking\ClickableFrame.h"
#include "UI\TriggerEventButton.h"

class Quickplay : public kitten::K_Component
{
private:
	puppy::TextBox* m_serverStatus;		// Status of the server: Online or Offline
	puppy::TextBox* m_playerCount;		// # players connected to the server 
	puppy::TextBox* m_activeSessions;	// # of active game sessions

	userinterface::TriggerEventButton* m_findGameButton;
	kitten::ClickableFrame* m_findGameButtonFrame;

	bool m_joiningSession = false;

	virtual void start() override;
	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;
public:
	Quickplay();
	~Quickplay();

	void pollForServer();
	void pollForServerListener(kitten::Event::EventType p_type, kitten::Event* p_event);

	void findGame();
	void findGameListener(kitten::Event::EventType p_type, kitten::Event* p_event);

	void startGame();
	void startGameListener(kitten::Event::EventType p_type, kitten::Event* p_event);

	void setServerInfoListener(kitten::Event::EventType p_type, kitten::Event* p_event);
	void setServerStatus(int p_status);
	void setPlayerCount(int p_count);
	void setActiveSessions(int p_count);
};
