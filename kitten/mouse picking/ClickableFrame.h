#pragma once

#include "kitten\K_Component.h"
#include <glm/glm.hpp>
#include <unordered_set>

namespace kitten
{
	class ClickableUI;

	class ClickableFrame : public K_Component, public TransformScaleListener
	{

	public:
		enum PivotType {
			piv_Left,
			piv_Right,
			piv_Top,
			piv_Bot,
			piv_Center,
			piv_BotLeft,
			piv_BotRight,
			piv_TopLeft,
			piv_TopRight
		};

		ClickableFrame(PivotType p_piv);
		~ClickableFrame();

		virtual void start() override;
		virtual void onScaleChanged(const glm::vec3& p_newScale) override;

		void addCLickable(ClickableUI* p_toAdd);
		void removeClickable(ClickableUI* p_toAdd);

		const glm::vec2& getMinPoint() const { return m_minPoint; };
		const glm::vec2& getMaxPoint() const { return m_maxPoint; };

		void onHoverStart();
		void onClick();
		void onHoverEnd();
		void release();

	private:
		std::unordered_set<ClickableUI*> m_listeners;
		glm::vec2 m_minPoint, m_maxPoint;
		glm::vec2 m_originalMinPoint, m_originalMaxPoint;
		PivotType m_piv;
	};
}
