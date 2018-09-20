#pragma once

#include "kitten\K_Component.h"
#include <glm/glm.hpp>

namespace kitten
{
	class Clickable : public K_Component
	{
	private:
		glm::vec3 m_minPoint, m_maxPoint;

	public:
		Clickable(const glm::vec3& p_pointMin, const glm::vec3& p_pointMax);
		virtual ~Clickable();

		const glm::vec3& getMinPoint() const { return m_minPoint; };
		const glm::vec3& getMaxPoint() const { return m_maxPoint; };

		virtual void onClick() = 0;
		virtual void onHoverStart();
		virtual void onHoverEnd();
	};
}