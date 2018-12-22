#include "Clickable.h"
#include "ClickableBox.h"
#include "kitten\K_GameObject.h"

namespace kitten
{
	Clickable::Clickable(bool p_enabledOnPause) : m_attachedBox(nullptr), m_enabledOnPause(p_enabledOnPause)
	{

	}

	Clickable::~Clickable()
	{
		m_attachedBox->removeClickable(this);
	}

	void Clickable::start()
	{
		// You MUST call this method or add yourself as a ClickableBox when overriding this class
		ClickableBox* box = m_attachedObject->getComponent<ClickableBox>();
		if (box == nullptr)
		{
			assert(false); //Every clickable needs a bounding box to be clicked on!
			return;
		}

		box->addClickable(this);
		m_attachedBox = box;
	}

	void Clickable::onHoverStart()
	{
		//Empty to not force override
	}

	void Clickable::onClick()
	{
		//Empty to not force override
	}

	void Clickable::onHoverEnd()
	{
		//Empty to not force override
	}

	void Clickable::onPause()
	{
		//Empty to not force override
	}

	void Clickable::onUnpause()
	{
		//Empty to not force override
	}
}