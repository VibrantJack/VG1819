#include "Status.h"
#include "unit/Unit.h"

namespace ability
{
	int Status::effect()
	{
		return -1;
	}
	int Status::effect(TimePointEvent p_timePoint)
	{
		return -1;
	}
	int Status::effect(TimePointEvent p_timePoint, ability::AbilityInfoPackage * p_pack)
	{
		return -1;
	}
	int Status::effect(TimePointEvent p_timePoint, int p_value)
	{
		return -1;
	}
	Status::Status()
	{
	}
	Status::~Status()
	{
	}

	void Status::attach(unit::Unit * p_u)
	{
		m_unit = p_u; 
		p_u->addStatus(this);
	}

	void Status::removeThis()
	{
		m_unit->removeStatus(this);
		delete this;
	}

	int Status::changeCounter(const std::string & p_cName, int p_value)
	{
		if (m_counter.find(p_cName) != m_counter.end())
		{
			m_counter[p_cName] += p_value;
			return 0;
		}
		//not find target counter
		return 1;
	}

	void Status::checkDuration()
	{
		if (m_counter.find("duration") != m_counter.end())
		{
			if (m_counter["duration"] <= 0)
			{
				removeThis();
			}
		}
	}
}

