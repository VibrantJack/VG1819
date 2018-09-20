#include "ActiveClickables.h"

namespace kitten
{
	ActiveClickables* ActiveClickables::sm_instance = nullptr;

	void ActiveClickables::addToActive(Clickable* p_toAdd)
	{
		m_clickables.push_back(p_toAdd);
	}

	void ActiveClickables::removeFromActive(Clickable* p_toRemove)
	{
		auto end = m_clickables.cend();
		for (auto it = m_clickables.begin(); it != end; ++it)
		{
			if (*it == p_toRemove)
			{
				m_clickables.erase(it);
				return;
			}
		}
	}

	const std::list<Clickable*>& ActiveClickables::getClickableList() const
	{
		return m_clickables;
	}
}