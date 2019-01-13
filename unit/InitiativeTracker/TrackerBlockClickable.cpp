#include "TrackerBlockClickable.h"
#include "kitten/K_Common.h"
#include <iostream>
namespace unit
{
	TrackerBlockClickable::TrackerBlockClickable()
	{
	}

	TrackerBlockClickable::~TrackerBlockClickable()
	{
	}

	void TrackerBlockClickable::onClick()
	{
		//std::cout << "Block CLICKED..........." << std::endl;
	}

	void TrackerBlockClickable::onHoverStart()
	{
		//m_txtGO->setEnabled(true);
		m_context->setEnabled(true);
	}

	void TrackerBlockClickable::onHoverEnd()
	{
		//m_txtGO->setEnabled(false);
		m_context->setEnabled(false);
	}

	void TrackerBlockClickable::onPause()
	{
		//m_txtGO->setEnabled(false);
		m_context->setEnabled(false);
	}

	//DEPRECATED METHOD
	void TrackerBlockClickable::setTextBox(kitten::K_GameObject * p_txt)
	{
		//m_txtGO = p_txt;
		//m_txtGO->setEnabled(false);
	}

	void TrackerBlockClickable::setContext(CardContext* p_context)
	{
		m_context = p_context;
	}
}
