#include "ClickableUI.h"
#include "ClickableFrame.h"
#include "kitten\K_GameObject.h"

namespace kitten
{
	ClickableUI::ClickableUI() : m_attachedFrame(nullptr)
	{

	}

	ClickableUI::~ClickableUI()
	{
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
}