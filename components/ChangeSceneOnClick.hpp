#pragma once
#include "kitten/mouse picking/ClickableUI.h"
#include <string>

class ChangeSceneOnClick : public kitten::ClickableUI {
private:
	const std::string m_targetScene;
public:
	void onClick();
	
	ChangeSceneOnClick(const std::string& p_scene);
	~ChangeSceneOnClick();
};