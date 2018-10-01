#pragma once
#include "ability/status/Status.h"

//Rock

namespace ability
{
	Status_CD::Status_CD()
	{

	}

	int Status_CD::effect(TimePointEvent p_timePoint)
	{
		if (p_timePoint == ability::Turn_Start)
		{
			//reduce all counter by 1
			changeCounter();
		}
		return 0;
	}
}