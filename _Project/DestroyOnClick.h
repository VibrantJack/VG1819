#pragma once
#include "kitten\mouse picking\Clickable.h"

class DestroyOnClick : public kitten::Clickable
{
public:
	DestroyOnClick(const glm::vec3& p_minPoint, const glm::vec3& p_maxPoint);
	~DestroyOnClick();

	virtual void onClick() override;
};