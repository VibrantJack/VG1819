#pragma once

#include <string>
#include "kitten\mouse picking\Clickable.h"

class PrintWhenClicked : public kitten::Clickable
{
private:
	std::string m_message;
public:
	PrintWhenClicked(const glm::vec3& p_minPoint, const glm::vec3& p_maxPoint, const std::string& p_message);
	virtual ~PrintWhenClicked();

	virtual void onClick() override;
};