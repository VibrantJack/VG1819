#pragma once

#include "kitten\K_Component.h"
#include "kitten\InputManager.h"

class ToggleStringInputOnKeyPress : public kitten::K_Component
{
private:
	char m_key;
	input::InputManager* m_inputMan;

public:
	ToggleStringInputOnKeyPress(char p_key);
	ToggleStringInputOnKeyPress(nlohmann::json& p_json);
	~ToggleStringInputOnKeyPress();

	virtual bool hasUpdate() const override { return true; }
	virtual void update() override;

	virtual void start() override;
};