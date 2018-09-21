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

	void Clickable::onAttached()
	{
		m_minPoint = m_originalMinPoint * getTransform().getScale();
		m_maxPoint = m_originalMaxPoint * getTransform().getScale();

		getTransform().addScaleListener(this);
	}

	void Clickable::onHoverStart()
	{
		//Debug
		std::cout << "min point: " << m_minPoint[0] << ", " << m_minPoint[1] << ", " << m_minPoint[2] << std::endl;
		std::cout << "max point: " << m_maxPoint[0] << ", " << m_maxPoint[1] << ", " << m_maxPoint[2] << std::endl;
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