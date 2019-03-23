#include "ItemSpawnArea.h"

ItemSpawnArea::ItemSpawnArea()
{
}

ItemSpawnArea::~ItemSpawnArea()
{
}

void ItemSpawnArea::check()
{
	if (m_delay > 0)//there's delay before first spawn
	{
		m_delay--;
		return;
	}

	m_turnPass++;
	if (m_turnPass < m_turnWait)//there's wait between each spawn
	{
		return;
	}

	//spawn item
	//check empty tile

}

void ItemSpawnArea::setProperty(nlohmann::json * p_jsonfile)
{
	m_itemPerSpawn = p_jsonfile->operator[]("item_per_spawn");

	m_turnWait = p_jsonfile->operator[]("turn_for_next_spawn");

	m_delay = p_jsonfile->operator[]("delay");

	m_itemPath = p_jsonfile->operator[]("item_path");

	m_texturePath = p_jsonfile->operator[]("texture");
}
