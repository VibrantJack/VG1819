#include "AmbientSystemController.h"

#include "UniversalPfx.h"
#include "util\MathUtil.h"

#include  <random>

AmbientSystemController::AmbientSystemController(const std::vector<AmbientEvent>& p_ambientEvents, const std::vector<kitten::AudioSource*> p_persistentSounds)
	: m_kTime(nullptr), m_ambientEvents(p_ambientEvents)
{
	auto end = m_ambientEvents.cend();
	for (auto it = m_ambientEvents.cbegin(); it != end; ++it)
	{
		(*it).gameObject->setEnabled(false);
	}

	auto pEnd = p_persistentSounds.cend();
	for (auto it = p_persistentSounds.cbegin(); it != pEnd; ++it)
	{
		m_persistentSounds.push_back(PersistentSound((*it), (*it)->getVolume()));
	}
}

AmbientSystemController::~AmbientSystemController()
{

}

void AmbientSystemController::start()
{
	m_kTime = kitten::K_Time::getInstance();
	assert(m_kTime != nullptr);

	// Play persistent sounds
	auto end = m_persistentSounds.cend();
	for (auto it = m_persistentSounds.cbegin(); it != end; ++it)
	{
		(*it).sound->play();
	}
}

void AmbientSystemController::update()
{
	float deltaTime = m_kTime->getDeltaTime();

	auto end = m_ambientEvents.end();
	for (auto it = m_ambientEvents.begin(); it != end; ++it)
	{
		(*it).update(deltaTime);

		if ((*it).isReady())
		{
			//Move the GO back to its place just incase it has something that moves it
			const glm::vec3& place = (*it).place;
			(*it).gameObject->getTransform().place(place.x, place.y, place.z);

			(*it).gameObject->setEnabled(true);

			(*it).reset();
		}
	}
}