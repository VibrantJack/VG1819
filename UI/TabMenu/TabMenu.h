#pragma once
#include "UI\UIFrame.h"
#include "kitten\InputManager.h"
#include "kitten\event_system\EventManager.h"

class TabMenu : public userinterface::UIFrame
{
private:
	input::InputManager* m_input;
	bool m_bOpened;
	bool m_bGameEnded;

	kitten::K_GameObject* m_returnToMainButton;
	userinterface::UIObject* m_endGameScreenObj;

	void enableEndGameScreen(kitten::Event::EventType p_type, kitten::Event* p_data);
public:
	TabMenu(const char* p_pathToTex);
	~TabMenu();

	virtual void start() override;

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;
};