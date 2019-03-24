#pragma once
#include "kitten\K_Component.h"
#include "kitten\Camera.h"
#include "kitten\InputManager.h"
#include "board\BoardManager.h"

class TogglePhotoModeOnKeyPress : public kitten::K_Component
{
private:
	char m_key;
	kitten::Camera* m_camera;
	input::InputManager* m_inputMan;
	BoardManager* m_boardMan;

	virtual void start() override;
	
	virtual bool hasUpdate() const override { return true; }
	virtual void update() override;

public:
	TogglePhotoModeOnKeyPress(char p_key);
	~TogglePhotoModeOnKeyPress();
};