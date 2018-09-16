#include "ChangeHPNode.h"
#include "Unit/Unit.h"

int ChangeHPNode :: effect(Unit * p_target, int p_value)
{
	p_target->m_attributes["HP"] += p_value;
	if (p_target->m_attributes["HP"] > p_target->m_attributes["MaxHP"])
		p_target->m_attributes["HP"] = p_target->m_attributes["MaxHP"];

	/*p_target->m_HP += p_value;
	if (p_target->m_HP > p_target->m_MaxHP)
		p_target->m_HP = p_target->m_MaxHP;
	*/
	//else if (p_target->m_HP <= 0)
		//p_target->destroyedByDamage();
	return 0;
}
