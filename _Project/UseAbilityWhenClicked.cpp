#include "UseAbilityWhenClicked.h"
#include "ability\AbilityManager.h"
#include "kitten\K_GameObject.h"
#include "unit\Unit.h"

UseAbilityWhenClicked::UseAbilityWhenClicked()
{

}

UseAbilityWhenClicked::~UseAbilityWhenClicked()
{

}

void UseAbilityWhenClicked::onClick()
{
	ability::AbilityInfoPackage* info = new ability::AbilityInfoPackage();

	// Highlight tiles that can be manipulated, for testing, do all
	for (int x = 0; x < 15; x++) 
	{
		for (int z = 0; z < 15; z++)
		{
			info->m_targetTiles.push_back(std::make_pair(x, z));
		}
	}
	unit::Unit* unit = m_attachedObject->getComponent<unit::Unit>();
	info->m_source = unit;

	ability::AbilityManager::getInstance()->useAbility(MANIPULATE_TILE_ABILITY, info);
}