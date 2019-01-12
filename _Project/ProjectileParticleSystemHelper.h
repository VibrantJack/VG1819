#pragma once
#include "kitten\K_Component.h"
#include "kitten\K_ParticleSystem.h"

#include <string>

class ProjectileParticleSystemHelper : public kitten::K_Component
{
private:
	const std::string m_effectName;
	bool m_disabledOnce;

	virtual void onDisabled() override;
public:
	ProjectileParticleSystemHelper(const std::string& p_effectName);
	~ProjectileParticleSystemHelper();
};