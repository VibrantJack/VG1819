#include "ZoomByMouseWheel.h"
#include "kitten\K_GameObject.h"
#include "kitten\InputManager.h"

ZoomByMouseWheel::ZoomByMouseWheel(float p_speed, int p_minFOV, int p_maxFOV) : m_cam(nullptr), m_speed(p_speed), m_minFOV(p_minFOV), m_maxFOV(p_maxFOV)
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
			int currentFOV = m_cam->getFOV();
			int nextFOV = currentFOV + (mouseWheel*m_speed);

			//Clamp FOV between values
			if (nextFOV > m_minFOV && nextFOV < m_maxFOV)
			{
				m_cam->setFOV(nextFOV);
			}
		}
	}
}
