#pragma once

#include "kitten\K_Component.h"
#include "kitten\InputManager.h"
#include "kitten\K_ParticleSystem.h"

class RefreshParticleSystemOnKeyPress : public kitten::K_Component
{
private:

	char m_key;
	kitten::K_ParticleSystem* m_particleSystem;
	input::InputManager* m_inputMan;

	virtual void start() override;

	virtual bool hasUpdate() const override
	{
		return true;
	}
	virtual void update() override;

public:
	RefreshParticleSystemOnKeyPress(char p_key);
	~RefreshParticleSystemOnKeyPress();
};