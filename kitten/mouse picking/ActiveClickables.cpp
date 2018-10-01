#include "ActiveClickables.h"

namespace kitten
{
	ActiveClickables* ActiveClickables::sm_instance = nullptr;

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
}