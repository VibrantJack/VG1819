// LandContext
//
// Displays information about the hovered tile
// Hides off screen and appears when you click the button
// 
//
// @Ken

#pragma once
#include "kitten\K_Component.h"
#include "_Project/LerpController.h"
#include "kitten\event_system\EventManager.h"
#include "board\tile\TileInfo.h"
#include "puppy\Text\TextBox.h"
#include "UI\UIObject.h"

class LandContext : public kitten::K_Component, public LerpController::PositionLerpFinishedCallback
{
private:
	puppy::TextBox* m_name = nullptr;
	puppy::TextBox* m_description = nullptr;
	kitten::K_GameObject* m_button = nullptr;
	kitten::K_GameObject* m_background = nullptr;
	userinterface::UIObject* m_landPortrait = nullptr;

	TileInfo* m_tileInfo = nullptr;
	LerpController* m_lerpController = nullptr;

	glm::vec3 m_enabledPos;
	glm::vec3 m_disabledPos;
	bool m_enabling = false;

public:
	LandContext();
	~LandContext();

	virtual void start() override;

	void setTileInfo(TileInfo* p_tileInfo);
	void setTileInfoListener(kitten::Event::EventType p_type, kitten::Event* p_event);
	void updateContext();

	void addLerpCallback(kitten::Event::EventType p_type, kitten::Event* p_event);
	void setEnabledListener(kitten::Event::EventType p_type, kitten::Event* p_event);
	virtual void onPositionLerpFinished(kitten::K_GameObject* p_obj) override;
};