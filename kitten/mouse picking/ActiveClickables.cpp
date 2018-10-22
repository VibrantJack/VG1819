#include "ActiveClickables.h"

namespace kitten
{
	ActiveClickables* ActiveClickables::sm_instance = nullptr;

	ActiveClickables::ActiveClickables() : m_lastHover(nullptr), m_lastUIHover(nullptr)
	{

	}

	ActiveClickables::~ActiveClickables()
	{

	}

	void ActiveClickables::addToActive(ClickableBox* p_toAdd)
	{
		m_clickables.push_back(p_toAdd);
	}

	void ActiveClickables::removeFromActive(ClickableBox* p_toRemove)
	{
		auto end = m_clickables.cend();
		for (auto it = m_clickables.begin(); it != end; ++it)
		{
			if (*it == p_toRemove)
			{
				m_clickables.erase(it);

				if (p_toRemove == m_lastHover)
				{
					m_lastHover = nullptr;
				}
				return;
			}
		}
	}

	const std::list<ClickableBox*>& ActiveClickables::getClickableList() const
	{
		return m_clickables;
	}

	void ActiveClickables::addToActiveUI(ClickableFrame* p_toAdd)
	{
		m_UIclickables.push_back(p_toAdd);
	}

	void ActiveClickables::removeFromActiveUI(ClickableFrame* p_toRemove)
	{
		auto end = m_UIclickables.cend();
		for (auto it = m_UIclickables.begin(); it != end; ++it)
		{
			if (*it == p_toRemove)
			{
				m_UIclickables.erase(it);

				if (p_toRemove == m_lastUIHover)
				{
					m_lastHover = nullptr;
				}

				return;
			}
		}
	}

	const std::list<ClickableFrame*>& ActiveClickables::getClickableUIList() const
	{
		return m_UIclickables;
	}
}