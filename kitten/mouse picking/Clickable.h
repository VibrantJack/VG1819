#pragma once

#include "kitten\K_Component.h"
#include <glm/glm.hpp>

namespace kitten
{
	//@TODO: Make clickable update its min and max when the attached transform's scale is changed
	class Clickable : public K_Component, public TransformScaleListener
	{
	private:
		glm::vec3 m_minPoint, m_maxPoint;
		glm::vec3 m_originalMinPoint, m_originalMaxPoint;

	public:
		Clickable(const glm::vec3& p_pointMin, const glm::vec3& p_pointMax);
		virtual ~Clickable();

		virtual void onAttached() override;

		const glm::vec3& getMinPoint() const { return m_minPoint; };
		const glm::vec3& getMaxPoint() const { return m_maxPoint; };

		virtual void onClick() = 0;
		virtual void onHoverStart();
		virtual void onHoverEnd();

		virtual void onScaleChanged(const glm::vec3& p_newScale) override;
	};
}