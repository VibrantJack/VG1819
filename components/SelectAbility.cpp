#include "components\SelectAbility.h"
#include "unit\Unit.h"

SelectAbility::SelectAbility()
{

}

SelectAbility::~SelectAbility()
{

}

void SelectAbility::useAbility(AbilityType p_ability)
{
	ability::AbilityInfoPackage* info = new ability::AbilityInfoPackage();
	unit::Unit* unit = m_attachedObject->getComponent<unit::Unit>();
	switch (p_ability)
	{
		case SelectAbility::Manipulate_Tile:
		{
			//tile list will be determined in board manager using range 
			/*
			for (int x = 0; x < 15; x++)
			{
				for (int z = 0; z < 15; z++)
				{
					info->m_targetTiles.push_back(std::make_pair(x, z));
				}
			}*/
			info->m_source = unit;

			ability::AbilityManager::getInstance()->useAbility(MANIPULATE_TILE_ABILITY, info);
			break;
		}
		case SelectAbility::Summon_Unit:
		{
			//tile list will be determined in board manager using range 
			/*
			kitten::Transform& transform = m_attachedObject->getTransform();
			float unitOffsetX = 0.5f;
			glm::vec3 pos = transform.getTranslation();

			// @TODO
			// Need a better way to access tiles, current implementation assumes tiles based on 
			// position of the unit
			if (pos.x + unitOffsetX - 1 >= 0)
			{
				info->m_targetTiles.push_back(std::make_pair(pos.x + unitOffsetX - 1, pos.z));
				printf("1pushed tile %f, %f\n", pos.x + unitOffsetX - 1, pos.z);
			}
			if (pos.x + unitOffsetX + 1 < 15)
			{
				info->m_targetTiles.push_back(std::make_pair(pos.x + unitOffsetX + 1, pos.z));
				printf("2pushed tile %f, %f\n", pos.x + unitOffsetX + 1, pos.z);
			}
			if (pos.z - 1 >= 0)
			{
				info->m_targetTiles.push_back(std::make_pair(pos.x + unitOffsetX, pos.z - 1));
				printf("3pushed tile %f, %f\n", pos.x + unitOffsetX, pos.z - 1);
			}
			if (pos.z + 1 < 15)
			{
				info->m_targetTiles.push_back(std::make_pair(pos.x + unitOffsetX, pos.z + 1));
				printf("4pushed tile %f, %f\n", pos.x + unitOffsetX, pos.z + 1);
			}*/
			info->m_source = unit;
			ability::AbilityManager::getInstance()->useAbility(SUMMON_UNIT, info);
			break;
		}
		default:
			break;
	}
}