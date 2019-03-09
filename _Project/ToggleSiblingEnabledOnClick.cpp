#include "ToggleSiblingEnabledOnClick.h"

ToggleSiblingEnabledOnClick::ToggleSiblingEnabledOnClick() : m_sibling(nullptr)
{

}

ToggleSiblingEnabledOnClick::~ToggleSiblingEnabledOnClick()
{

}

void ToggleSiblingEnabledOnClick::start()
{
	ClickableUI::start();

	const auto& transform = getTransform();
	const auto parent = getTransform().getParent();
	assert(parent != nullptr);
	
	const auto& children = parent->getChildren();
	
	auto end = children.cend();
	for (auto it = children.cbegin(); it != end; ++it)
	{
		m_sibling = &(*it)->getAttachedGameObject();
		
		if (m_sibling != m_attachedObject)
		{
			return;
		}
	}

	assert(false, "GameObject has no sibling to toggle, but has toggle sibling component");
}

void ToggleSiblingEnabledOnClick::onClick()
{
	m_sibling->setEnabled(!m_sibling->isEnabled());
}