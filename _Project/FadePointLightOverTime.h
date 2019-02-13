#pragma once

#include "kitten\lights\K_PointLight.h"
#include "kitten\K_Time.h"

class FadePointLightOverTime : public kitten::K_Component
{
private:
	kitten::K_PointLight* m_pointLight;
	kitten::K_Time* m_time;

	float m_timeToFade, m_timeElapsed;
	glm::vec3 m_startingAttenuation;
	glm::vec3 m_endingAttenuation;

	virtual void start() override;
	virtual void onEnabled() override;
	virtual void onDisabled() override;

	virtual bool hasUpdate() const override { return true; }
	virtual void update() override;

public:
	FadePointLightOverTime(float p_timeToFade, const glm::vec3& p_endingAttenuation);
	~FadePointLightOverTime();

	void setTimeToFade(float p_timeToFade);
};