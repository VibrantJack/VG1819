#pragma once
#include "kitten\K_Component.h"
#include "puppy\Text\TextBox.h"
#include "kitten\InputManager.h"

class TabMenu : public kitten::K_Component
{
private:
	input::InputManager* m_input;
	bool m_bOpened;

	kitten::K_GameObject* m_returnToMainButton;
public:
	TabMenu();
	~TabMenu();

	virtual void start() override;

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;
};