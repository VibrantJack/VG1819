#pragma once
#include "kitten/mouse picking/ClickableUI.h"
#include <string>

class ChangeSceneOnClick : public kitten::ClickableUI {
private:
	std::string m_targetScene;
public:
	void onClick();

	virtual void onPreSwitch();

	ChangeSceneOnClick(const std::string& p_scene);
	~ChangeSceneOnClick();
};