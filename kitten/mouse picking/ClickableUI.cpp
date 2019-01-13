#include "ClickableUI.h"
#include "ClickableFrame.h"
#include "kitten\K_GameObject.h"

namespace kitten
{
	void ClickableUI::onDisabled()
	{
		if(m_attachedFrame != nullptr)
			m_attachedFrame->removeClickable(this);
	}
	void ClickableUI::onEnabled()
	{
		if (m_attachedFrame != nullptr)
			m_attachedFrame->addCLickable(this);
	}
	ClickableUI::ClickableUI(bool p_enabledOnPause) : m_attachedFrame(nullptr), m_enabledOnPause(p_enabledOnPause)
	{
		
	}

	ClickableUI::~ClickableUI()
	{
		if (m_attachedFrame == nullptr || !m_isEnabled) return;
		m_attachedFrame->removeClickable(this);
	}

	void ClickableUI::start()
	{
		ClickableFrame* frame = m_attachedObject->getComponent<ClickableFrame>();
		if (frame == nullptr)
		{
			assert(false);
			return;
		}

		frame->addCLickable(this);
		m_attachedFrame = frame;
	}

	void ClickableUI::onHoverStart()
	{
		//Empty to not force override
	}

	void ClickableUI::onClick()
	{
		//Empty to not force override
	}

	void ClickableUI::onHoverEnd()
	{
		//Empty to not force override
	}

	void ClickableUI::release()
	{
		//empty to not force override
	}

	void ClickableUI::onPause()
	{
		//Empty to not force override
	}

	void ClickableUI::onUnpause()
	{
		//Empty to not force override
	}
}