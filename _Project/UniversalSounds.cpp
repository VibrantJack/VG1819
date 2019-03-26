#include "UniversalSounds.h"
#include "kitten\K_GameObjectManager.h"

UniversalSounds* UniversalSounds::sm_instance = nullptr;

UniversalSounds::UniversalSounds(const std::list<std::pair<std::string, std::string>>& p_sounds) : m_soundsToCreate(p_sounds), m_volume(1.0)
{
	assert(sm_instance == nullptr);
	sm_instance = this;
}

UniversalSounds::~UniversalSounds()
{
	assert(sm_instance == this);
	sm_instance = nullptr;
}

void UniversalSounds::start()
{
	kitten::K_GameObjectManager::getInstance()->flagGameObjectToSurvive(m_attachedObject);

	auto end = m_soundsToCreate.cend();
	for (auto it = m_soundsToCreate.cbegin(); it != end; ++it)
	{
		auto soundName = (*it).first;
		auto soundPath = (*it).second;

		auto createdSound = kitten::K_GameObjectManager::getInstance()->createNewGameObject(soundPath);
		kitten::AudioSource* createdAudioSource = createdSound->getComponent<kitten::AudioSource>();

		SoundEntry entry(createdAudioSource, createdAudioSource->getVolume());

		m_sounds.insert(std::make_pair(soundName, entry));

		createdSound->getTransform().setParent(&(getTransform()));
	}

	m_soundsToCreate.clear();

	privateSetVolume(m_volume);
}

void UniversalSounds::playSound(const std::string& p_sound)
{
	sm_instance->privatePlaySound(p_sound);
}

void UniversalSounds::privatePlaySound(const std::string& p_sound) const
{
	auto found = m_sounds.find(p_sound);
	if (found != m_sounds.cend())
	{
		(*found).second.source->play();
	}
}

void UniversalSounds::playSound(const std::string& p_soundName, const glm::vec3& p_place)
{
	sm_instance->privatePlaySound(p_soundName, p_place);
}

void UniversalSounds::privatePlaySound(const std::string& p_soundName, const glm::vec3& p_place) const
{
	auto found = m_sounds.find(p_soundName);
	if (found != m_sounds.cend())
	{
		(*found).second.source->getTransform().place(p_place.x, p_place.y, p_place.z);
		(*found).second.source->play();
	}
}

void UniversalSounds::setVolume(float p_volume)
{
	sm_instance->privateSetVolume(p_volume);
}

void UniversalSounds::privateSetVolume(float p_volume)
{
	auto end = m_sounds.cend();
	for (auto it = m_sounds.cbegin(); it != end; ++it)
	{
		auto entry = (*it).second;
		auto soundSource = entry.source;

		float nextVolume = p_volume * entry.originalVolume;

		soundSource->setVolume(nextVolume);
	}

	m_volume = p_volume;
}

float UniversalSounds::getVolume()
{
	return sm_instance->m_volume;
}