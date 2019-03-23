#include "ItemKeepArea.h"

ItemKeepArea::ItemKeepArea(int p_id)
	:m_clientId(p_id)
{
}

ItemKeepArea::~ItemKeepArea()
{
}

void ItemKeepArea::check()
{
	for (auto info : m_tileList)
	{
		if (info->hasUnit())//this tile has unit on it
		{
			//get unit
			kitten::K_GameObject* ugo = info->getUnit();
			unit::Unit* u = ugo->getComponent<unit::Unit>();

			//check if unit is ally
			if (m_clientId != u->m_clientId)
				continue;

			//if unit has item

			//remove item

			//increase points
		}
	}
}

void ItemKeepArea::setProperty(nlohmann::json * p_jsonfile)
{
	m_pointPerItem = p_jsonfile->operator[]("point_per_item");

	m_texturePath = p_jsonfile->operator[]("texture");
}
