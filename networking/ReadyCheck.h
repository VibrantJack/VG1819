#pragma once
#include "UI/UIElement.h"
#include "kitten\event_system\EventManager.h"
#include "puppy\Text\TextBox.h"
#include "UI\TriggerEventButton.h"
#include "_Project/LerpController.h"

class ReadyCheck : public userinterface::UIElement, public LerpController::PositionLerpFinishedCallback
{
private:
	puppy::TextBox* m_textbox = nullptr;
	userinterface::TriggerEventButton* m_readyButton = nullptr;
	LerpController* m_lerpController = nullptr;
	const char* m_messages[3];

	glm::vec3 m_origin = glm::vec3(0.0f, 0.0f, 0.0f);
	float m_timeElapsed = 0.0f;
	int m_messageIndex = 0;
	bool m_update = true;
	bool m_startGame = false;
public:

	ReadyCheck(const char* p_pathToTex);
	ReadyCheck(const char* p_pathToTex, pivotType p_pivot, textureBehaviour p_texBehaviour);
	virtual ~ReadyCheck();

	virtual void start() override;
	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

	void playersReadyListener(kitten::Event::EventType p_type, kitten::Event* p_data);
	void playerJoinedListener(kitten::Event::EventType p_type, kitten::Event* p_data);
	void readyButtonClicked(kitten::Event::EventType p_type, kitten::Event* p_data);

	virtual void onPositionLerpFinished() override;
};