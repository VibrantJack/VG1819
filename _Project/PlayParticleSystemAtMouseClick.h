#pragma once

#include "kitten\K_Component.h"
#include "kitten\event_system\EventManager.h"
#include "kitten\K_ParticleSystem.h"

class PlayParticleSystemAtMouseClick : public kitten::K_Component
{
private:

	kitten::K_ParticleSystem* m_particleSystem;
	const glm::vec3 m_offset;

	virtual void start() override;

	virtual void onEnabled() override;
	virtual void onDisabled() override;

public:
	PlayParticleSystemAtMouseClick(const glm::vec3& p_offset);
	~PlayParticleSystemAtMouseClick();
	
	void onMouseClick(kitten::Event::EventType p_type, kitten::Event* p_event);
};