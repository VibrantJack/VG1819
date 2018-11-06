#include "ActiveClickables.h"
#include "ClickableUI.h"
#include "kitten\K_ComponentManager.h"

//austin's clickable ui frame (bounding box for clickables)

namespace kitten
{
	ClickableFrame::ClickableFrame(PivotType p_piv)
	{
		ActiveClickables::getInstance()->addToActiveUI(this);
		m_piv = p_piv;
	}

	ClickableFrame::~ClickableFrame()
	{
		ActiveClickables::getInstance()->removeFromActiveUI(this);

		auto it = m_listeners.begin();
		while (it != m_listeners.end())
		{
			kitten::K_ComponentManager::getInstance()->destroyComponentImmediate(*it);
			it = m_listeners.begin();
		}
	}

	void ClickableFrame::start()
	{
		switch (m_piv)
		{
			case piv_Right:
			{
				m_minPoint = glm::vec2(-1.0f, -0.5f);
				m_maxPoint = glm::vec2(0.0f, 0.5f);
				break;
			}
			case piv_Left:
			{
				m_minPoint = glm::vec2(0.0f, -0.5f);
				m_maxPoint = glm::vec2(1.0f, 0.5f);
				break;
			}
			case piv_Top:
			{
				m_minPoint = glm::vec2(-0.5f, -1.0f);
				m_maxPoint = glm::vec2(0.5f, 0.0f);
				break;
			}
			case piv_Bot:
			{
				m_minPoint = glm::vec2(-0.5f, 0.0f);
				m_maxPoint = glm::vec2(0.5f, 1.0f);
				break;
			}
			case piv_TopRight:
			{
				m_minPoint = glm::vec2(-1.0f, -1.0f);
				m_maxPoint = glm::vec2(0.0f, 0.0f);
				break;
			}
			case piv_BotRight:
			{
				m_minPoint = glm::vec2(-1.0f, 0.0f);
				m_maxPoint = glm::vec2(0.0f, 1.0f);
				break;
			}
			case piv_TopLeft:
			{
				m_minPoint = glm::vec2(0.0, -1.0f);
				m_maxPoint = glm::vec2(1.0f, 0.0f);
				break;
			}
			case piv_BotLeft:
			{
				m_minPoint = glm::vec2(0.0f, 0.0f);
				m_maxPoint = glm::vec2(1.0f, 1.0f);
				break;
			}
			case piv_Center:
			{
				m_minPoint = glm::vec2(-0.5, -0.5);
				m_maxPoint = glm::vec2(0.5f, 0.5f);
			}
		}
		
		getTransform().addScaleListener(this);
	}

	void ClickableFrame::addCLickable(ClickableUI* p_toAdd)
	{
		m_listeners.insert(p_toAdd);
	}

	void ClickableFrame::removeClickable(ClickableUI* p_toRemove)
	{
		m_listeners.erase(p_toRemove);
	}

	void ClickableFrame::onScaleChanged(const glm::vec3& p_newScale)
	{
		glm::vec2 scale2D = glm::vec2(p_newScale.x, p_newScale.y);

		m_minPoint = m_originalMinPoint * scale2D;
		m_maxPoint = m_originalMaxPoint * scale2D;
	}

	void ClickableFrame::onHoverStart()
	{
		auto end = m_listeners.cend();
		for (auto it = m_listeners.begin(); it != end; ++it)
		{
			(*it)->onHoverStart();
		}
	}

	void ClickableFrame::onClick()
	{
		auto end = m_listeners.cend();
		for (auto it = m_listeners.begin(); it != end; ++it)
		{
			(*it)->onClick();
		}
	}

	void ClickableFrame::onHoverEnd()
	{
		auto end = m_listeners.cend();
		for (auto it = m_listeners.begin(); it != end; ++it)
		{
			(*it)->onHoverEnd();
		}
	}
}