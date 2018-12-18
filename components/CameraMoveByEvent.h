#pragma once
#include "kitten\K_Component.h"
#include "kitten/Camera.h"
#include "kitten/event_system/EventManager.h"

class CameraMoveByEvent : public kitten::K_Component
{
private:
	kitten::Camera* m_cam;

public:

	CameraMoveByEvent();
	virtual ~CameraMoveByEvent();

	virtual void start() override;
	virtual void onEnabled() override;
	virtual void onDisabled() override;

	void moveCameraListener(kitten::Event::EventType p_type, kitten::Event* p_event);
};