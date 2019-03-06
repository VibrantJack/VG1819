#include "BGMManager.h"
#include "kitten\K_GameObjectManager.h"

BGMManager* BGMManager::sm_instance = nullptr;

BGMManager::BGMManager(const std::list<std::pair<std::string, std::string>>& p_soundsToCreate) : m_soundsToCreate(p_soundsToCreate)
{
	assert(sm_instance == nullptr);
	sm_instance = this;
}

BGMManager::~BGMManager()
{
	assert(sm_instance == this);
	sm_instance = nullptr;
}

void BGMManager::start()
{
	kitten::K_GameObjectManager::getInstance()->flagGameObjectToSurvive(m_attachedObject);

	auto end = m_soundsToCreate.cend();
	for (auto it = m_soundsToCreate.cbegin(); it != end; ++it)
	{
		auto soundName = (*it).first;
		auto soundPath = (*it).second;

		auto createdSound = kitten::K_GameObjectManager::getInstance()->createNewGameObject(soundPath);
		kitten::AudioSource* createdAudioSource = createdSound->getComponent<kitten::AudioSource>();

		BGMEntry entry(createdAudioSource, createdAudioSource->getVolume());

		m_tracks.insert(std::make_pair(soundName, entry));

		createdSound->getTransform().setParent(&(getTransform()));
	}

	m_soundsToCreate.clear();
}

void BGMManager::playBGM(const std::string& p_name)
{
	sm_instance->privatePlayBGM(p_name);
}

void BGMManager::stopBGM()
{
	sm_instance->privateStopBGM();
}

void BGMManager::privatePlayBGM(const std::string& p_name)
{
	auto found = m_tracks.find(p_name);
	assert(found != m_tracks.end());

	auto source = (*found).second.source;
	source->play();

	m_playingSource = source;
}

void BGMManager::privateStopBGM()
{
	if (m_playingSource != nullptr)
	{
		m_playingSource->stop();
		m_playingSource = nullptr;
	}
}

void BGMManager::setVolume(float p_volume)
{
	sm_instance->setVolume(p_volume);
}

void BGMManager::privateSetVolume(float p_volume)
{
	auto end = m_tracks.cend();
	for (auto it = m_tracks.cbegin(); it != end; ++it)
	{
		auto& entry = (*it).second;
		entry.source->setVolume(p_volume * entry.originalVolume);
	}
}