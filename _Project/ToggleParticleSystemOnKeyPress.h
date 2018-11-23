#pragma once
#include "kitten\K_Component.h"
#include "kitten\K_ParticleSystem.h"
#include "kitten\InputManager.h"

class ToggleParticleSystemOnKeyPress : public kitten::K_Component
{
private:
	char m_key;
	kitten::K_ParticleSystem* m_particleSystem;
	input::InputManager* m_inputMan;

	virtual bool hasUpdate() const override { return true; }
	virtual void update() override;

	virtual void start() override;

public:
	ToggleParticleSystemOnKeyPress(char p_key);
	~ToggleParticleSystemOnKeyPress();


};