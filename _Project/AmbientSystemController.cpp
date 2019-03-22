#include "AmbientSystemController.h"

#include "UniversalPfx.h"
#include "util\MathUtil.h"

#include  <random>

AmbientSystemController::AmbientSystemController(const std::vector<AmbientEvent>& p_ambientEvents, float p_minEventTime, float p_maxEventTIme) 
	: m_kTime(nullptr), m_currentTime(0), m_timeToNextEvent(0), m_minTimeToEvent(p_minEventTime), m_maxTimeToEvent(p_maxEventTIme), m_ambientEvents(p_ambientEvents)
{
	auto end = m_ambientEvents.cend();
	for (auto it = m_ambientEvents.cbegin(); it != end; ++it)
	{
		(*it).gameObject->setEnabled(false);
	}
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
		//Move the GO back to its place just incase it has something that moves it
		const glm::vec3& place = m_nextEvent->place;
		m_nextEvent->gameObject->getTransform().place(place.x, place.y, place.z);

		m_nextEvent->gameObject->setEnabled(true);

		onNextEventNeeded();
	}
}

void AmbientSystemController::onNextEventNeeded()
{
	m_timeToNextEvent = LERP(((float)rand() / (float)RAND_MAX), m_minTimeToEvent, m_maxTimeToEvent);
	m_currentTime = 0;

	// Get a random next event
	int index = std::rand() % m_ambientEvents.size();
	m_nextEvent = &(m_ambientEvents[index]);
}
