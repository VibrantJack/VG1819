#include "NewTurnMessageController.h"
#include "kitten/K_Time.h"

unit::NewTurnMessageController::NewTurnMessageController(float p_time)
	:m_display(nullptr),
	m_time(p_time),
	m_currentTime(0)
{
}

unit::NewTurnMessageController::~NewTurnMessageController()
{
}

void unit::NewTurnMessageController::setDisplay(TurnChangeDisplay * p_display)
{
	m_display = p_display;
}

void unit::NewTurnMessageController::start()
{
}

bool unit::NewTurnMessageController::hasUpdate() const
{
	return true;
}

void unit::NewTurnMessageController::update()
{
	if (m_show)
	{
		m_currentTime += kitten::K_Time::getInstance()->getDeltaTime();
		if (m_currentTime >= m_time)
			m_attachedObject->setEnabled(false);
	}
}

void unit::NewTurnMessageController::onEnabled()
{
	m_show = true;
	m_currentTime = 0;
}

void unit::NewTurnMessageController::onDisabled()
{
	assert(m_display != nullptr);
	m_show = false;
}
