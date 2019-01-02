#pragma once
#include "kitten/mouse picking/ClickableUI.h"
#include <string>

class SetupDeckEditOnSceneChange : public kitten::ClickableUI {
private:
	const std::string m_targetScene;
public:
	void onClick();

	SetupDeckEditOnSceneChange(const std::string& p_scene);
	~SetupDeckEditOnSceneChange();
};