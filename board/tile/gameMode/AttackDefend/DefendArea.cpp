#include "DefendArea.h"

//constant value

//defend side player need to defend 25 turns
static const int s_DefendPointPerTurn = 4;

//set attacker and defender id
static const int s_attackerId = 0;
static const int s_defenderId = 1;

DefendArea::DefendArea()
{
}

DefendArea::~DefendArea()
{
}

void DefendArea::check()
{
	int counter = 0; //point of attacker
	for (auto info : m_tileList)
	{
		if (info->hasUnit())//this tile has unit on it
		{
			//get unit
			kitten::K_GameObject* ugo = info->getUnit();
			unit::Unit* u = ugo->getComponent<unit::Unit>();

			//check unit client id
			int id = u->m_clientId;

			//check unit lv, high lv unit grants more points
			int lv = u->m_attributes[UNIT_LV];
			int pt = lv > 0 ? lv : 1;

			if (id == s_attackerId)
				counter += pt;
		}
	}

	//attacker gain points based on units
	GameModeManager::getInstance()->gainPoint(s_attackerId, counter);

	//defender gain points for this turn
	GameModeManager::getInstance()->gainPoint(s_defenderId, s_DefendPointPerTurn);

	//Both players can gain points, so they may reach max point at same time
	//Attacker will win in this situation
}
