#include "CameraMoveByEvent.h"
#include "_Project/LerpController.h"

CameraMoveByEvent::CameraMoveByEvent()
{

}

CameraMoveByEvent::~CameraMoveByEvent()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Move_Camera, this);
}


void CameraMoveByEvent::start()
{
	m_cam = m_attachedObject->getComponent<kitten::Camera>();
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Move_Camera,
		this,
		std::bind(&CameraMoveByEvent::onCameraEvent, this, std::placeholders::_1, std::placeholders::_2));
}

void CameraMoveByEvent::onEnabled()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Move_Camera,
		this,
		std::bind(&CameraMoveByEvent::onCameraEvent, this, std::placeholders::_1, std::placeholders::_2));
}

void CameraMoveByEvent::onDisabled()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Move_Camera, this);
}

void CameraMoveByEvent::onCameraEvent(kitten::Event::EventType p_type, kitten::Event* p_event)
{
	m_cam->setFOV(p_event->getFloat(CAM_FOV));

	float time = p_event->getFloat("time");
	if(time <= 0)//directly move
		m_cam->getTransform().place(p_event->getFloat(POSITION_X), m_CameraPosY, p_event->getFloat(POSITION_Z));
	else
	{//set lerp
		glm::vec3 target(p_event->getFloat(POSITION_X), m_CameraPosY, p_event->getFloat(POSITION_Z));
		LerpController* lc = m_attachedObject->getComponent<LerpController>();
		if (lc->isLerping())
		{
			lc->forceLerpToFinish(false);
		}
		lc->positionLerp(target, time);
	}
}
