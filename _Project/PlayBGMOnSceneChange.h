#pragma once

#include "kitten\K_Component.h"
#include "kitten\event_system\EventManager.h"

#include <unordered_map>

class PlayBGMOnSceneChange : public kitten::K_Component
{
private:
	const std::unordered_map<std::string, std::string> m_bgmMap;

	virtual void onEnabled() override;
	virtual void onDisabled() override;
	virtual void start() override;

	void onSceneChanged(kitten::Event::EventType p_type, kitten::Event* p_event);

public:
	PlayBGMOnSceneChange(const std::unordered_map<std::string, std::string>& p_bgmMap);
	~PlayBGMOnSceneChange();
};