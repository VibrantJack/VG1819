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

	int Status::removeThis()
	{
		m_unit->removeStatus(this);
		delete this;
		return 0;
	}
}

