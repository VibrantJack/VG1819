#pragma once
#include "kitten/K_Component.h"

class PlaySoundOnStart : public kitten::K_Component
{
public:
	PlaySoundOnStart();
	PlaySoundOnStart(nlohmann::json& p_json);
	~PlaySoundOnStart();

	void start() override;
};