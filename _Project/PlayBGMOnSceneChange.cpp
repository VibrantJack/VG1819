#include "PlayBGMOnSceneChange.h"

#include "BGMManager.h"
#include "kitten\K_GameObjectManager.h"

PlayBGMOnSceneChange::PlayBGMOnSceneChange(const std::unordered_map<std::string, std::string>& p_bgmMap) : m_bgmMap(p_bgmMap)
{
	onEnabled();
}

PlayBGMOnSceneChange::~PlayBGMOnSceneChange()
{
	if (m_isEnabled)
	{
		onDisabled();
	}
}

void PlayBGMOnSceneChange::start()
{
	kitten::K_GameObjectManager::getInstance()->flagGameObjectToSurvive(m_attachedObject);
}

void PlayBGMOnSceneChange::onEnabled()
{
	kitten::EventManager::getInstance()->addListener(kitten::Event::Scene_Change, this,
		std::bind(&PlayBGMOnSceneChange::onSceneChanged, this, std::placeholders::_1, std::placeholders::_2));
}

void PlayBGMOnSceneChange::onDisabled()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::Scene_Change, this);
}

void PlayBGMOnSceneChange::onSceneChanged(kitten::Event::EventType p_type, kitten::Event* p_event)
{
	auto found = m_bgmMap.find(p_event->getString(NEXT_SCENE_PATH_KEY));
	if (found != m_bgmMap.cend())
	{
		BGMManager::playBGM((*found).second);
	}
}