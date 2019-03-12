#pragma once
#include "kitten\K_Component.h"
#include "kitten\InputManager.h"

class ToggleChildEnabledOnKeyPress : public kitten::K_Component
{
private:
	char m_key;
	input::InputManager* m_inputMan;

public:
	ToggleChildEnabledOnKeyPress(char p_key);
	~ToggleChildEnabledOnKeyPress();

	bool hasUpdate() const override { return true; };

	void start() override;
	void update() override;
};
