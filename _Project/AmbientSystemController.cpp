#include "AmbientSystemController.h"

AmbientSystemController::AmbientSystemController(float p_minEventTime, float p_maxEventTIme) : m_kTime(nullptr),
m_currentTime(0), m_timeToNextEvent(0), m_minTimeToEvent(p_minEventTime), m_maxTimeToEvent(p_maxEventTIme)
{

}

AmbientSystemController::~AmbientSystemController()
{

}

void AmbientSystemController::start()
{
	m_kTime = kitten::K_Time::getInstance();
	assert(m_kTime != nullptr);

	onNextEventNeeded();
}

void AmbientSystemController::update()
{
	m_currentTime += m_kTime->getDeltaTime();
	if (m_currentTime >= m_timeToNextEvent)
	{
		switch (m_nextEvent)
		{
		case wind:
			// Get place to blow wind
			// Play wind sound
			// Play wind particles (?)
			break;
		case crickets:
			// Same as wind, but with crickets
			break;
		case frogs:
			// Same as wind, but with frogs
			break;
		case sword_in_stone_shine:
			// Get the sword's place
			// play shine sound
			// play shiny particles
			break;
		case fae:
			// same as wind, but with fae
			break;
		}

		onNextEventNeeded();
	}
}

void AmbientSystemController::onNextEventNeeded()
{
	m_timeToNextEvent = LERP(((float)rand() / (float)RAND_MAX), m_minTimeToEvent, m_maxTimeToEvent);
	m_currentTime = 0;

	m_nextEvent = (AmbientEvent)(rand() % AmbientEvent::COUNT);
}