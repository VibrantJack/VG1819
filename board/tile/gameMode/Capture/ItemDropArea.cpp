#include "ItemDropArea.h"

ItemDropArea::ItemDropArea(int p_id, ItemSpawnArea* p_area)
	:m_clientId(p_id),
	m_spawnArea(p_area)
{
}

ItemDropArea::~ItemDropArea()
{
}

void ItemDropArea::check()
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

void ItemDropArea::setProperty(nlohmann::json * p_jsonfile)
{
	m_pointPerItem = p_jsonfile->operator[]("point_per_item");

	m_texturePath = p_jsonfile->operator[]("texture");
}
