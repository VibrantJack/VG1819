#include "ActionButton.h"

#define REGULAR_TEXTURE "textures/ui/buttons/blank_button.tga"
#define HIGHLIGHTED_TEXTURE "textures/ui/buttons/blank_button_highlighted.tga"

unit::ActionButton::ActionButton()
	:
	m_render(nullptr),
	m_regularTexture(REGULAR_TEXTURE),
	m_highlightedTexture(HIGHLIGHTED_TEXTURE)
{
}

unit::ActionButton::~ActionButton()
{
}

void unit::ActionButton::start()
{
	Clickable::start();
	m_render = m_attachedObject->getComponent<kitten::QuadRenderable>();
	assert(m_render != nullptr);
	m_render->setTexture(m_regularTexture.c_str());

	m_select = m_attachedObject->getComponent<ActionSelect>();
	assert(m_render != nullptr);
}

void unit::ActionButton::onDisabled()
{
	if (m_render != nullptr)
		m_render->setTexture(m_regularTexture.c_str());
}

void unit::ActionButton::onClick()
{
	m_select->act();
}

void unit::ActionButton::onHoverStart()
{
	m_render->setTexture(m_highlightedTexture.c_str());
}

void unit::ActionButton::onHoverEnd()
{
	m_render->setTexture(m_regularTexture.c_str());
}
