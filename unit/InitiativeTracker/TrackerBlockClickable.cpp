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
		m_txtGO->setEnabled(true);
	}

	void TrackerBlockClickable::onHoverEnd()
	{
		m_txtGO->setEnabled(false);
	}

	void TrackerBlockClickable::setTextBox(kitten::K_GameObject * p_txt)
	{
		m_txtGO = p_txt;
		m_txtGO->setEnabled(false);
	}
}
