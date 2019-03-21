#include "AmbientSystemController.h"

#include "UniversalPfx.h"

AmbientSystemController::AmbientSystemController(const glm::vec2& p_minPoint, const glm::vec2& p_maxPoint, float p_minEventTime, float p_maxEventTIme) : m_kTime(nullptr),
m_currentTime(0), m_timeToNextEvent(0), m_minTimeToEvent(p_minEventTime), m_maxTimeToEvent(p_maxEventTIme), m_minPoint(p_minPoint), m_maxPoint(p_maxPoint)
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
			playGenericEvent("wind");
			break;
		case crickets:
			playGenericEvent("crickets");
			break;
		case frogs:
			playGenericEvent("frogs");
			break;
		case sword_in_stone_shine:
			// Get the sword's place
			// play shine sound
			// play shiny particles
			break;
		case fae:
			playGenericEvent("fae");
			break;
		}

		onNextEventNeeded();
	}
}

void AmbientSystemController::playGenericEvent(const std::string& p_name, int p_randomIndex, int p_randMax) const
{
	std::string eventName = p_name;

	if (p_randomIndex > 0)
	{
		eventName += "_" + std::to_string((rand() % p_randMax) + 1);
	}
	
	glm::vec3 pos = getEventPos();

	UniversalPfx::getInstance()->playEffect(eventName, pos); 
	// If the effect has an associated sound, it should play it itself
}

glm::vec3 AmbientSystemController::getEventPos() const
{
	float y = 0.01f; // Y value is always the same

	float x = LERP(((float)rand() / (float)RAND_MAX), m_minPoint.x, m_maxPoint.x);
	float z = LERP((float)rand() / (float)RAND_MAX, m_minPoint.y, m_maxPoint.y);

	return glm::vec3(x, y, z);
}

void AmbientSystemController::onNextEventNeeded()
{
	switch (m_nextEvent) // m_nextEvent is really the previous event now
	{
	default:
		m_timeToNextEvent = LERP(((float)rand() / (float)RAND_MAX), m_minTimeToEvent, m_maxTimeToEvent);
		m_currentTime = 0;

		m_nextEvent = (AmbientEvent)(rand() % AmbientEvent::COUNT);
		break;
	}
}
