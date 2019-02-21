#pragma once
#include "kitten\K_Component.h"
#include "kitten\audio\AudioSource.h"
#include "kitten\InputManager.h"

class PlaySoundOnKeyPress : public kitten::K_Component
{
private:
	kitten::AudioSource* m_audioSource;
	char m_key;

	input::InputManager* m_inputMan;
public:
	PlaySoundOnKeyPress(char p_key);
	PlaySoundOnKeyPress(nlohmann::json& p_json);
	~PlaySoundOnKeyPress();

	void start() override;
	bool hasUpdate() const override { return true; }

	void update() override;
};