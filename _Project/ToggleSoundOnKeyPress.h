#pragma once
#include "kitten\K_Component.h"
#include "kitten\audio\AudioSource.h"
#include "kitten\InputManager.h"

class ToggleSoundOnKeyPress : public kitten::K_Component
{
private:
	kitten::AudioSource* m_audioSource;
	char m_key;
	input::InputManager* m_inputMan;

public:
	ToggleSoundOnKeyPress(char p_key);
	~ToggleSoundOnKeyPress();

	void start() override;

	bool hasUpdate() const override { return true; }
	void update() override;
};