#pragma once

#include "kitten\K_Component.h"
#include "kitten\K_ParticleSystem.h"

class PlayParticleSystemOnEnable : public kitten::K_Component
{
private:
	kitten::K_ParticleSystem* m_particleSystem;

	virtual void start() override;
	virtual void onEnabled() override;

public:
	PlayParticleSystemOnEnable();
	~PlayParticleSystemOnEnable();
};