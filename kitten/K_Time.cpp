#include <time.h>
#include "glfw\include\GL\glfw.h"

#include "K_Time.h"

namespace kitten
{
	K_Time* K_Time::sm_instance = nullptr;

	K_Time::K_Time()
	{
		m_startTime = glfwGetTime();
		m_deltaTime = 0;
		m_elapsedTime = m_startTime;
	}

	K_Time::~K_Time()
	{

	}

	void K_Time::updateTime()
	{
		double currentTime = glfwGetTime();
		m_deltaTime = currentTime - m_elapsedTime;
		m_elapsedTime = currentTime;
	}
}
