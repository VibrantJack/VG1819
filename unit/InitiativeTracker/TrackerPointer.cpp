#include "TrackerPointer.h"
#include "kitten/K_ComponentManager.h"
#include "kitten/K_GameObjectManager.h"

unit::TrackerPointer::TrackerPointer()
{
	
}

unit::TrackerPointer::~TrackerPointer()
{
}

void unit::TrackerPointer::start()
{
	K_Component* comFrame = kitten::K_ComponentManager::getInstance()->createComponent("PointerUI");
	m_attachedObject->addComponent(comFrame);
	scale();
}

bool unit::TrackerPointer::hasUpdate() const
{
	return true;
}

void unit::TrackerPointer::update()
{
	float velocity = kitten::K_Time::getInstance()->getDeltaTime() * m_speed * 60.0f;
	if (m_scaleUp)
	{
		m_scale += velocity;
		if (m_scale >= m_maxScale)
			m_scaleUp = false;

	}
	else
	{
		m_scale -= velocity;
		if (m_scale <= m_minScale)
			m_scaleUp = true;
	}
	scale();
}

void unit::TrackerPointer::scale()
{
	m_attachedObject->getTransform().scale2D(m_scale, m_scale);

	float y = m_y - m_scale / 2.0f;
	m_attachedObject->getTransform().place2D(m_x, y);
}
