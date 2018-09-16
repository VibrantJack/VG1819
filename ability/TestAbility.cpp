#include "TestAbility.h"


TestAbility::TestAbility(Unit* p_u) :Ability(p_u)
{
	m_description = "Damage Self by 1 and gain one Counter.";
	addNode(new ChangeHPNode());
	addNode(new ChangeCounterNode());
}

int TestAbility::effect()
{
	//test node, so things are hard coded

	//change hp
	m_abilityNodes[0]->effect(m_unit,-1);
	//change counter
	m_abilityNodes[1]->effect(m_unit, "dC", 1);

	return 0;
}
