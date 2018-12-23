// ClickableButton
//
// Abstract class to be used for UI Buttons which defines
// the onHoverStart and onHoverEnd behaviour for the buttons
// Inheriting classes need only to override onClick to define
// specific button behaviour on click
//
// Note: Regular Font size vs Highlighted Font size ratio 0.9815
//
// @Ken

#include "UI\ClickableButton.h"

#define REGULAR_TEXTURE "textures/ui/buttons/blank_button.tga"
#define HIGHLIGHTED_TEXTURE "textures/ui/buttons/blank_button_highlighted.tga"
#define INACTIVE_TEXTURE "textures/ui/buttons/disabled_button.tga"

namespace userinterface
{
	ClickableButton::ClickableButton(bool p_enabledOnPause)
		:
		ClickableUI(p_enabledOnPause),
		m_uiObject(nullptr),
		m_regularTexture(REGULAR_TEXTURE),
		m_highlightedTexture(HIGHLIGHTED_TEXTURE),
		m_inactiveTexture(INACTIVE_TEXTURE),
		m_active(true)
	{

	}

	ClickableButton::~ClickableButton()
	{

	}

	void ClickableButton::start()
	{
		ClickableUI::start();
		m_uiObject = static_cast<UIObject*>(m_attachedObject->getComponent<UIObject>());
		assert(m_uiObject != nullptr);
	}

	void ClickableButton::onDisabled()
	{
		m_active = true;

		if (m_uiObject != nullptr)
			m_uiObject->setTexture(m_regularTexture.c_str());
	}

	void ClickableButton::onHoverStart()
	{
		if (!m_active)
			return;

		m_uiObject->setTexture(m_highlightedTexture.c_str());
	}

	void ClickableButton::onHoverEnd()
	{
		if (!m_active)
			return;

		m_uiObject->setTexture(m_regularTexture.c_str());
	}

	void ClickableButton::onPause()
	{
		if (m_uiObject->getTexturePath() == m_highlightedTexture)
		{
			onHoverEnd();
		}
	}

	void ClickableButton::setActive(bool p_a)
	{
		if (m_active != p_a)
		{
			m_active = p_a;

			if (m_active)
			{
				m_uiObject->setTexture(m_regularTexture.c_str());
			}
			else
			{
				m_uiObject->setTexture(m_inactiveTexture.c_str());
			}
		}
	}
}