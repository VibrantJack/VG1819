#include "AmbientSystemController.h"

#include "UniversalPfx.h"
#include "settings_menu\PlayerPrefs.h"
#include "util\MathUtil.h"

#include  <random>

AmbientSystemController* AmbientSystemController::sm_instance = nullptr;

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

	assert(sm_instance == nullptr);
	sm_instance = this;
}

AmbientSystemController::~AmbientSystemController()
{
	assert(sm_instance == this);
	sm_instance = nullptr;
}

AmbientSystemController* AmbientSystemController::getInstance()
{
	return sm_instance;
}

void AmbientSystemController::setVolume(float p_volume)
{
	m_volume = p_volume;

	// Set persistent sounds volumes
	auto end = m_persistentSounds.cend();
	for (auto it = m_persistentSounds.cbegin(); it != end; ++it)
	{
		(*it).sound->setVolume(p_volume * (*it).volume);
	}
}

float AmbientSystemController::getVolume() const
{
	return m_volume;
}

void AmbientSystemController::start()
{
	m_kTime = kitten::K_Time::getInstance();
	assert(m_kTime != nullptr);

	setVolume((float)PlayerPrefs::getAmbientVolume() / 100.0f);

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