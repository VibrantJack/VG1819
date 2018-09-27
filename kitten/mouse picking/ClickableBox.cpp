#include "ActiveClickables.h"
#include "Clickable.h"
#include "kitten\K_ComponentManager.h"

namespace kitten
{
	ClickableBox::ClickableBox(const glm::vec3& p_minPoint, const glm::vec3& p_maxPoint) : m_originalMinPoint(p_minPoint), m_originalMaxPoint(p_maxPoint)
	{
		ActiveClickables::getInstance()->addToActive(this);
		m_minPoint = m_originalMinPoint;
		m_maxPoint = m_originalMaxPoint;
	}

	ClickableBox::~ClickableBox()
	{
		ActiveClickables::getInstance()->removeFromActive(this);

		auto it = m_listeners.begin();
		while(it != m_listeners.end())
		{
			kitten::K_ComponentManager::getInstance()->destroyComponentImmediate(*it);
			it = m_listeners.begin();
		}
	}

	void ClickableBox::start()
	{
		m_minPoint = m_originalMinPoint * getTransform().getScale();
		m_maxPoint = m_originalMaxPoint * getTransform().getScale();

		getTransform().addScaleListener(this);
	}

	void ClickableBox::addClickable(Clickable* p_toAdd)
	{
		m_listeners.push_back(p_toAdd);
	}

	void ClickableBox::removeClickable(Clickable* p_toRemove)
	{
		auto end = m_listeners.end();
		for (auto it = m_listeners.begin(); it != end; ++it)
		{
			if (*it == p_toRemove)
			{
				m_listeners.erase(it);
				return;
			}
		}
	}

	void ClickableBox::onScaleChanged(const glm::vec3& p_newScale)
	{
		m_minPoint = m_originalMinPoint * p_newScale;
		m_maxPoint = m_originalMaxPoint * p_newScale;
	}

	void ClickableBox::onHoverStart()
	{
		auto end = m_listeners.cend();
		for (auto it = m_listeners.begin(); it != end; ++it)
		{
			(*it)->onHoverStart();
		}
	}

	void ClickableBox::onClick()
	{
		auto end = m_listeners.cend();
		for (auto it = m_listeners.begin(); it != end; ++it)
		{
			(*it)->onClick();
		}
	}

	void ClickableBox::onHoverEnd()
	{
		auto end = m_listeners.cend();
		for (auto it = m_listeners.begin(); it != end; ++it)
		{
			(*it)->onHoverEnd();
		}
	}
}