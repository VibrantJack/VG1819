#pragma once
#include "kitten\K_Component.h"
#include "kitten/Camera.h"
#include "kitten/event_system/EventManager.h"

#define DEFAULT_CAMERA_POS_Y 13

class CameraMoveByEvent : public kitten::K_Component
{
private:
	kitten::Camera* m_cam;

	virtual void start() override;
	virtual void onEnabled() override;
	virtual void onDisabled() override;

	void onCameraEvent(kitten::Event::EventType p_type, kitten::Event* p_event);
public:
	CameraMoveByEvent();
	virtual ~CameraMoveByEvent();
};