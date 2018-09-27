#pragma once

#include "kitten\K_Component.h"
#include <glm/glm.hpp>
#include <list>

namespace kitten
{
	class Clickable;

	class ClickableBox : public K_Component, public TransformScaleListener
	{
	private:
		glm::vec3 m_minPoint, m_maxPoint;
		glm::vec3 m_originalMinPoint, m_originalMaxPoint;

		std::list<Clickable*> m_listeners;
	public:
		ClickableBox(const glm::vec3& p_minPoint, const glm::vec3& p_maxPoint);
		~ClickableBox();

		virtual void start() override;
		virtual void onScaleChanged(const glm::vec3& p_newScale) override;

		void addClickable(Clickable* p_toAdd);
		void removeClickable(Clickable* p_toRemove);

		const glm::vec3& getMinPoint() const { return m_minPoint; };
		const glm::vec3& getMaxPoint() const { return m_maxPoint; };

		void onHoverStart();
		void onClick();
		void onHoverEnd();
	};
}