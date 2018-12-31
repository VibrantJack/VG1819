#pragma once
#include "kitten\K_Component.h"

class MoveByMouseRightClickDrag : public kitten::K_Component
{
private:
	float m_speed;
	glm::vec2 m_minClamp, m_maxClamp;
public:
	
	MoveByMouseRightClickDrag(float p_speed, const glm::vec2& p_minClamp, const glm::vec2& p_maxClamp);
	virtual ~MoveByMouseRightClickDrag();

	virtual bool hasUpdate() const override;

	virtual void update() override;
};