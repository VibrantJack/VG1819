#pragma once
#include "kitten\K_Component.h"
#include "kitten\InputManager.h"
#include "UI\UIObject.h"
#include "_Project\LerpController.h"

#define MENU_TOP_ORIGINAL_VEC3_POS glm::vec3(0.0f, 560.0f, 0.0f)
#define MENU_BOTTOM_ORIGINAL_VEC3_POS glm::vec3(0.0f, -225.0f, 0.0f)

#define MENU_TOP_LERP_VEC3_POS glm::vec3(0.0f, 360.0f, 0.0f)
#define MENU_BOTTOM_LERP_VEC3_POS glm::vec3(0.0f, 0.0f, 0.0f)

#define MENU_LERP_TIME 0.75f

class MainMenu : public kitten::K_Component, public LerpController::PositionLerpFinishedCallback
{
private:
	input::InputManager* m_input;
	LerpController* m_menuTopController;
	LerpController* m_menuBottomController;

	kitten::K_GameObject* m_menuTop;
	kitten::K_GameObject* m_menuBottom;

public:
	MainMenu();
	~MainMenu();

	virtual void start() override;

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

	virtual void onPositionLerpFinished() override;
};