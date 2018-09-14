#include "ZoomByMouseWheel.h"
#include "kitten\K_GameObject.h"
#include "kitten\InputManager.h"

ZoomByMouseWheel::ZoomByMouseWheel(float p_speed) : m_cam(nullptr), m_speed(p_speed)
{

}

ZoomByMouseWheel::~ZoomByMouseWheel()
{

}

bool ZoomByMouseWheel::hasUpdate() const
{
	return true;
}

void ZoomByMouseWheel::update()
{
	if (m_cam == nullptr)
	{
		m_cam = m_attachedObject->getComponent<kitten::Camera>();
	}
	else // It's OK if we miss a frame
	{
		int mouseWheel = -1 * input::InputManager::getInstance()->getMouseWheel();
		if (mouseWheel != 0)
		{
			float currentFOV = m_cam->getFOV();
			float nextFOV = currentFOV + (mouseWheel*m_speed);

			//Clamp FOV between 1 and 90
			//@TODO: Set these values at runtime
			if (nextFOV > 1 && nextFOV < 90)
			{
				m_cam->setFOV(nextFOV);
			}
		}
	}
}
