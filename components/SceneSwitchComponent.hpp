#pragma once
#include "kitten/mouse picking/ClickableUI.h"
#include <string>

class SceneSwitchComponent : public kitten::ClickableUI {
	std::string m_targetScene;
public:
	void onClick();

	virtual void onPreSwitch();

	SceneSwitchComponent(std::string p_scene);
	~SceneSwitchComponent();
};