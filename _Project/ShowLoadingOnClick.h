#pragma once
#include "kitten\K_GameObject.h"
#include "kitten\mouse picking\ClickableUI.h"
#include "kitten\event_system\EventManager.h"

#define LOADING_SCREEN_JSON "UI/loading_screen.json"

class ShowLoadingOnClick : public kitten::ClickableUI
{
private:
	kitten::K_GameObject* m_loadingScreen;

	virtual void start() override;
	virtual void onClick() override;
public:
	ShowLoadingOnClick();
	~ShowLoadingOnClick();

	void disableLoadingScreen(kitten::Event::EventType p_type, kitten::Event* p_data);
};