#include "ControlArea.h"
#include "kitten/K_GameObject.h"

ControlArea::ControlArea()
{
}

ControlArea::~ControlArea()
{
}

void ControlArea::check()
{
	std::vector<int> counter = { 0,0 };//number of units on control area that belongs to player
	for (auto info : m_tileList)
	{
		if (info->hasUnit())//this tile has unit on it
		{
			//get unit
			kitten::K_GameObject* ugo = info->getUnit();
			unit::Unit* u = ugo->getComponent<unit::Unit>();

			//check unit client id
			int id = u->m_clientId;

			if (id >= 0)
				counter[id]++;
		}
	}

	//after check all tiles
	//if one player dominate area and the other player has no unit on it,
	//the first player gain point
	if (counter[0] > 0 && counter[1] == 0)
	{
		GameModeManager::getInstance()->gainPoint(0, counter[0]);
	}
	else if (counter[0] == 0 && counter[1] > 0)
	{
		GameModeManager::getInstance()->gainPoint(1, counter[1]);
	}
}
