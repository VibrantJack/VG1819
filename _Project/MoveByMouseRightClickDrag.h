#pragma once
#include "kitten\K_Component.h"

class MoveByMouseRightClickDrag : public kitten::K_Component
{
private:
	float m_speed = 1.0f;

public:
	
	MoveByMouseRightClickDrag(float p_speed = 1.0f);
	virtual ~MoveByMouseRightClickDrag();

	virtual bool hasUpdate() const override;

	virtual void update() override;
};