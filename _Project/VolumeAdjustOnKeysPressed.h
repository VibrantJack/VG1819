#pragma once
#include "kitten\K_Component.h"
#include "kitten\audio\AudioSource.h"
#include "kitten\InputManager.h"

class VolumeAdjustOnKeysPressed : public kitten::K_Component
{
private:
	kitten::AudioSource* m_audioSource;
	char m_increaseKey, m_decreaseKey;
	float m_changeAmount;
	input::InputManager* m_inputMan;


public:
	VolumeAdjustOnKeysPressed(char p_increaseKey, char p_decreaseKey, float p_changeAmount);
	VolumeAdjustOnKeysPressed(nlohmann::json& p_json);
	~VolumeAdjustOnKeysPressed();

	void start() override;

	bool hasUpdate() const override { return true; }
	void update() override;
};