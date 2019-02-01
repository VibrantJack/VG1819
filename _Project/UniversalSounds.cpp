#include "UniversalSounds.h"
#include "kitten\K_GameObjectManager.h"

UniversalSounds* UniversalSounds::sm_instance = nullptr;

UniversalSounds::UniversalSounds(const std::list<std::pair<std::string, std::string>>& p_sounds)
{
	assert(sm_instance == nullptr);
	sm_instance = this;

	auto end = p_sounds.cend();
	for (auto it = p_sounds.cbegin(); it != end; ++it)
	{
		auto soundName = (*it).first;
		auto soundPath = (*it).second;

		auto createdSound = kitten::K_GameObjectManager::getInstance()->createNewGameObject(soundPath);
		kitten::AudioSource* createdAudioSource = createdSound->getComponent<kitten::AudioSource>();

		m_sounds.insert(std::make_pair(soundName, createdAudioSource));
	}
}

UniversalSounds::~UniversalSounds()
{
	assert(sm_instance == this);
	sm_instance = nullptr;
}

void UniversalSounds::start()
{
	kitten::K_GameObjectManager::getInstance()->flagGameObjectToSurvive(m_attachedObject);

	//parent our created sounds now that we have a transform
	auto end = m_sounds.cend();
	for (auto it = m_sounds.cbegin(); it != end; ++it)
	{
		auto source = (*it).second;
		auto transform = source->getTransform();

		transform.setParent(&(getTransform()));
	}
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
		(*found).second->play();
	}
}