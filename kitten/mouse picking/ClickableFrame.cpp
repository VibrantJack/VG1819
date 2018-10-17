#include "ActiveClickables.h"
#include "ClickableUI.h"
#include "kitten\K_ComponentManager.h"

//austin's clickable ui frame (bounding box for clickables)

namespace kitten
{
	ClickableFrame::ClickableFrame(const glm::vec2& p_minPoint, const glm::vec2& p_maxPoint)
	{
		ActiveClickables::getInstance()->addToActiveUI(this);
		m_minPoint = m_originalMinPoint;
		m_maxPoint = m_originalMaxPoint;
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
		glm::vec3 actualScale = getTransform().getScale();
		glm::vec3 actualTranslation = getTransform().getTranslation();

		glm::vec2 scale2D = glm::vec2(actualScale.x, actualScale.y); 
		glm::vec2 trans2D = glm::vec2(actualTranslation.x, actualTranslation.y);

		glm::vec2 scale = m_originalMinPoint * scale2D;
		glm::vec2 pos = m_originalMaxPoint * trans2D;

		getTransform().addScaleListener(this);
	}

	void ClickableFrame::addCLickable(ClickableUI* p_toAdd)
	{
		m_listeners.push_back(p_toAdd);
	}

	void ClickableFrame::removeClickable(ClickableUI* p_toRemove)
	{
		auto end = m_listeners.end();
		for (auto it = m_listeners.begin(); it != end; it++)
		{
			if (*it == p_toRemove)
			{
				m_listeners.erase(it);
				return;
			}
		}
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