#pragma once
#include "kitten/mouse picking/ClickableUI.h"

class StartGameOnClick : public kitten::ClickableUI
{
private:
	const std::string m_targetScene;
public:
	void onClick();

	StartGameOnClick(const std::string& p_scene): m_targetScene(p_scene) {}
	~StartGameOnClick() {}
};