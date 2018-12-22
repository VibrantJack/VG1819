#include "ClickableUI.h"
#include "ClickableFrame.h"
#include "kitten\K_GameObject.h"

namespace kitten
{
	ClickableUI::ClickableUI(bool p_enabledOnPause) : m_attachedFrame(nullptr), m_enabledOnPause(p_enabledOnPause)
	{
		
	}

	ClickableUI::~ClickableUI()
	{
		if (m_attachedFrame == nullptr) return;
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
		//m_enabledOnPause = false;
		printf("ClickableUI::start m_enabledOnPause: %d\n", m_enabledOnPause);
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
}