#include "TrackerBlockClickable.h"
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
		std::cout << "UI Frame is clicked "<<std::endl;
	}

	void TrackerBlockClickable::onHoverStart()
	{
	}

	void TrackerBlockClickable::onHoverEnd()
	{
	}
}
