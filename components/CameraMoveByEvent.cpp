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
		std::bind(&CameraMoveByEvent::moveCameraListener, this, std::placeholders::_1, std::placeholders::_2));
}

void CameraMoveByEvent::onEnabled()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Move_Camera,
		this,
		std::bind(&CameraMoveByEvent::moveCameraListener, this, std::placeholders::_1, std::placeholders::_2));
}

void CameraMoveByEvent::onDisabled()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Move_Camera, this);
}

void CameraMoveByEvent::moveCameraListener(kitten::Event::EventType p_type, kitten::Event* p_event)
{
	m_cam->setFOV(p_event->getFloat("FOV"));
	m_cam->getTransform().place(p_event->getFloat("x"), 0, p_event->getFloat("z"));
}
