#include "DisableAfterTime.h"
#include "kitten\K_GameObject.h"

DisableAfterTime::DisableAfterTime(float p_timeToDisable) : m_time(nullptr), m_timeToDisable(p_timeToDisable), m_elapsedTime(0)
{

}

DisableAfterTime::~DisableAfterTime()
{

}

void DisableAfterTime::start()
{
	m_time = kitten::K_Time::getInstance();
	assert(m_time != nullptr);
}

void DisableAfterTime::setTime(const float& p_time)
{
	m_timeToDisable = p_time;
}

void DisableAfterTime::update()
{
	m_elapsedTime += m_time->getDeltaTime();
	if (m_elapsedTime >= m_timeToDisable)
	{
		m_elapsedTime = 0;
		m_attachedObject->setEnabled(false);
	}
}