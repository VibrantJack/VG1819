#pragma once

#include "kitten\K_Component.h"
#include "kitten\K_Instance.h"

class LoadSceneOnStart : public kitten::K_Component
{
private:
	const std::string m_sceneName;

	virtual void start() override;
public:
	LoadSceneOnStart(nlohmann::json& p_json);
	LoadSceneOnStart(const std::string& p_sceneName);
	~LoadSceneOnStart();
};