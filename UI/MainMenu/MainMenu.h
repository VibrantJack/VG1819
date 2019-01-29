#pragma once
#include "kitten\K_Component.h"
#include "UI\UIObject.h"
#include "_Project\LerpController.h"
#include "kitten\event_system\EventManager.h"

#define MENU_LERP_TIME 0.75f

class MainMenu : public kitten::K_Component
{
private:
	LerpController* m_menuTopController = nullptr;

	static kitten::K_GameObject* sm_menuBottom;
	static kitten::K_GameObject* sm_menuTop;

public:
	MainMenu();
	~MainMenu();

	virtual void start() override;

	void sceneChangeListener(kitten::Event::EventType p_type, kitten::Event* p_data);
};