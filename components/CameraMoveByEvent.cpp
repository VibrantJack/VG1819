#include "CameraMoveByEvent.h"

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
	m_cam->getTransform().place(p_event->getFloat(POSITION_X), DEFAULT_CAMERA_POS_Y, p_event->getFloat(POSITION_Z));
}
