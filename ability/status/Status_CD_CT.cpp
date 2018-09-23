#pragma once
#include "ability/status/Status.h"

//Rock

namespace ability
{
	Status_CD_CT::Status_CD_CT()
	{

	}

	int Status_CD_CT::effect(TimePointEvent p_timePoint)
	{
		if (p_timePoint == ability::Turn_Start)
		{
			//reduce all counter by 1
			for (auto it : m_counter)
			{
				it.second -= 1;
			}
		}

		//TO DO: implement cast time result

		return 0;
	}
}