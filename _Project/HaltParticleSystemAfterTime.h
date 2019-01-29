#pragma once

#include "kitten\K_Component.h"
#include "kitten\K_ParticleSystem.h"
#include "kitten\K_Time.h"
#include "kitten\K_GameObject.h"

class HaltParticleSystemAfterTime : public kitten::K_Component
{
private:

	kitten::K_ParticleSystem* m_particleSystem;
	kitten::K_Time* m_time;

	float m_timeElapsed, m_timeToHalt;
	bool m_isStopping;

	virtual void start() override;
	virtual void onEnabled() override;
	virtual void onDisabled() override;
	
	virtual bool hasUpdate() const override
	{
		return true;
	}
	virtual void update() override;

public:
	HaltParticleSystemAfterTime(float p_time, bool p_isStopping);
	~HaltParticleSystemAfterTime();

	void setTime(float p_time)
	{
		m_timeToHalt = p_time;
	}
};