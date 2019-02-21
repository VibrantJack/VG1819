#pragma once
#include "kitten\K_Component.h"
#include "kitten\InputManager.h"

class ToggleEnabledOnKeyPress : public kitten::K_Component
{
private:
	char m_key;
	input::InputManager* m_inputMan;

public:
	ToggleEnabledOnKeyPress(char p_key);
	ToggleEnabledOnKeyPress(nlohmann::json& p_json);
	~ToggleEnabledOnKeyPress();

	bool hasUpdate() const override { return true; };

	void start() override;
	void update() override;

};