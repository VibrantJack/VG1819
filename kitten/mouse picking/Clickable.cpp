#include "Clickable.h"
#include "ActiveClickables.h"

namespace kitten
{
	Clickable::Clickable(const glm::vec3& p_pointMin, const glm::vec3& p_pointMax) : m_minPoint(p_pointMin), m_maxPoint(p_pointMax)
	{
		ActiveClickables::getInstance()->addToActive(this);
	}

	Clickable::~Clickable()
	{
		ActiveClickables::getInstance()->removeFromActive(this);
	}

	void Clickable::onHoverStart()
	{

	}

	void Clickable::onHoverEnd()
	{

	}
}