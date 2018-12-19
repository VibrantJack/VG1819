#pragma once
#include "kitten\K_Component.h"
#include "kitten\K_Time.h"

class DisableAfterTime : public kitten::K_Component
{
private:
	float m_elapsedTime, m_timeToDisable;
	kitten::K_Time* m_time;

	virtual void start() override;

	virtual bool hasUpdate() const override { return true; }
	virtual void update() override;
public:
	DisableAfterTime(float p_timeToDisable);
	~DisableAfterTime();

	void setTime(const float& p_time);
};