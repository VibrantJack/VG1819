#pragma once
#include "kitten/mouse picking/ClickableUI.h"
#include <string>

class ChangeSceneOnClick : public kitten::ClickableUI
{
private:
	std::string m_targetScene;

public:
	ChangeSceneOnClick(const std::string& p_scene);

	virtual void onClick() override;
};