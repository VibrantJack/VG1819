#include "Clickable.h"
#include "ActiveClickables.h"
#include <iostream>

namespace kitten
{
	Clickable::Clickable(const glm::vec3& p_pointMin, const glm::vec3& p_pointMax) : m_originalMinPoint(p_pointMin), m_originalMaxPoint(p_pointMax)
	{
		ActiveClickables::getInstance()->addToActive(this);
		m_minPoint = m_originalMinPoint;
		m_maxPoint = m_originalMaxPoint;
	}

	Clickable::~Clickable()
	{
		ActiveClickables::getInstance()->removeFromActive(this);
	}

	void Clickable::start()
	{
		m_minPoint = m_originalMinPoint * getTransform().getScale();
		m_maxPoint = m_originalMaxPoint * getTransform().getScale();

		getTransform().addScaleListener(this);
	}

	void Clickable::onHoverStart()
	{

	}

	void Clickable::onHoverEnd()
	{

	}

	void Clickable::onScaleChanged(const glm::vec3& p_newScale)
	{
		m_minPoint = m_originalMinPoint * p_newScale;
		m_maxPoint = m_originalMaxPoint * p_newScale;
	}
}