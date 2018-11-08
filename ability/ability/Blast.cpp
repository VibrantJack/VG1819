#include "ability/ability/Ability.h"
#include "unit/Unit.h"
#include "board/tile/TileInfo.h"
#include <iostream>
//Rock

namespace ability
{
	int Blast::effect(AbilityInfoPackage* p_info)
	{
		std::cout << "Blast Effect" << std::endl;
		std::vector<unit::Unit*> ulist;
		//get target first
		for (int i = 0; i < p_info->m_targetTilesGO.size(); i++)
		{
			TileInfo* info = p_info->m_targetTilesGO[i]->getComponent<TileInfo>();
			if (info->hasUnit())//if the tile has unit, push it into package
			{
				unit::Unit* u = info->getUnit()->getComponent<unit::Unit>();
				ulist.push_back(u);
			}
		}

		//trigger deal damage event
		unit::StatusContainer* sc = p_info->m_source->getStatusContainer();
		ability::TimePointEvent* t = new ability::TimePointEvent(ability::TimePointEvent::Deal_Damage);
		t->putPackage(INFO_PACKAGE_KEY, p_info);
		sc->triggerTP(ability::TimePointEvent::Deal_Damage, t);

		for (unit::Unit* u : ulist)
		{
			//trigger receive damage event
			sc = u->getStatusContainer();
			t = new ability::TimePointEvent(ability::TimePointEvent::Receive_Damage);

			//get copy of package
			AbilityInfoPackage* clonePackage = new AbilityInfoPackage(*p_info);
			t->putPackage(INFO_PACKAGE_KEY, clonePackage);
			sc->triggerTP(ability::TimePointEvent::Receive_Damage, t);

			int power = -(clonePackage->m_intValue.find("power")->second);

			damage(u, power);

			//delete clone
			delete clonePackage;
		}

		//delete package
		done(p_info);

		return 0;
	}

}
