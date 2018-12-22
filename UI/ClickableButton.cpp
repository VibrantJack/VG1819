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

namespace userinterface
{
	ClickableButton::ClickableButton(bool p_enabledOnPause)
		:
		ClickableUI(p_enabledOnPause),
		m_uiObject(nullptr),
		m_regularTexture(REGULAR_TEXTURE),
		m_highlightedTexture(HIGHLIGHTED_TEXTURE)
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
		if (m_uiObject != nullptr)
			m_uiObject->setTexture(m_regularTexture.c_str());
	}

	void ClickableButton::onHoverStart()
	{
		m_uiObject->setTexture(m_highlightedTexture.c_str());
	}

	void ClickableButton::onHoverEnd()
	{
		m_uiObject->setTexture(m_regularTexture.c_str());
	}
}