#include "Status_Demonic_Restriction.h"

#include "ability/AbilityMacro.h"
#include "unit/UnitCommon.h"

namespace ability
{
	Status_DR_AD_Change::Status_DR_AD_Change() : Status_Demonic_Restriction::Status_Demonic_Restriction()
	{
	}

	void Status_DR_AD_Change::restrictionOn()
	{
		changeEffectedAD();
	}

	void Status_DR_AD_Change::restrictionOff()
	{
		changeEffectedAD(true);
	}

	int Status_DR_AD_Change::effect()
	{
		setEffectedAD();
		return 0;
	}
}