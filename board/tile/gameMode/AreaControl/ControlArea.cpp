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

			//check points to gain
			int pt = m_pointPerUnit;
			if (m_pointPerUnit < 0)//use unit lv
			{
				//check unit lv, high lv unit grants more points
				int lv = u->m_attributes[UNIT_LV];
				pt = lv > 0 ? lv : 1;//unit without lv gain 1 point
			}

			if (id >= 0)
				counter[id]+= pt;
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

void ControlArea::setProperty(nlohmann::json * p_jsonfile)
{
	m_pointPerUnit = p_jsonfile->operator[]("point_per_unit");

	m_filePath = p_jsonfile->operator[]("tile");
}
