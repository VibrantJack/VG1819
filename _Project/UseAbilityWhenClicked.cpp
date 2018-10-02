#include "UseAbilityWhenClicked.h"
#include "ability\AbilityManager.h"

UseAbilityWhenClicked::UseAbilityWhenClicked()
{

}

UseAbilityWhenClicked::~UseAbilityWhenClicked()
{

}

void UseAbilityWhenClicked::onClick()
{
	printf("UseAbilityWhenClicked::onClick called\n");
	ability::AbilityInfoPackage* info = new ability::AbilityInfoPackage();

	// Highlight tiles that can be manipulated, for testing, do all
	for (int x = 0; x < 15; x++) 
	{
		for (int z = 0; z < 15; z++)
		{
			info->m_targetTiles.push_back(std::make_pair(x, z));
		}
	}
	ability::AbilityManager::getInstance()->useAbility("ManipulateTile", info);

	//info->m_intValue.insert(std::pair<std::string, int>("pos_x", 0));
	//info->m_intValue.insert(std::pair<std::string, int>("pos_y", 0));
	//ability::AbilityManager::getInstance()->useAbility("ManipulateTile", info);
}