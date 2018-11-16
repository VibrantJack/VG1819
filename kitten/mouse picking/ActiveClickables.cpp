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
		m_clickables.insert(p_toAdd);
	}

	void ActiveClickables::removeFromActive(ClickableBox* p_toRemove)
	{
		if (p_toRemove == m_lastHover)
		{
			m_lastHover = nullptr;
		}

		m_clickables.erase(p_toRemove);
	}

	const std::unordered_set<ClickableBox*>& ActiveClickables::getClickableList() const
	{
		return m_clickables;
	}

	void ActiveClickables::addToActiveUI(ClickableFrame* p_toAdd)
	{
		m_UIclickables.insert(p_toAdd);
	}

	void ActiveClickables::removeFromActiveUI(ClickableFrame* p_toRemove)
	{
		if (p_toRemove == m_lastUIHover)
		{
			m_lastUIHover = nullptr;
		}

		m_UIclickables.erase(p_toRemove);
	}

	const std::unordered_set<ClickableFrame*>& ActiveClickables::getClickableUIList() const
	{
		return m_UIclickables;
	}
}