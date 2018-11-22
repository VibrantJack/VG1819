#pragma once
#include "kitten/mouse picking/ClickableUI.h"
#include <string>

class SceneSwitchComponent : public kitten::ClickableUI {
private:
	std::string m_targetScene;
public:
	void onClick();

	virtual void onPreSwitch();

	SceneSwitchComponent(const std::string& p_scene);
	~SceneSwitchComponent();
};