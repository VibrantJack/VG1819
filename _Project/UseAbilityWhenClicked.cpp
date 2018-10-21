// UseAbilityWhenClicked
//
// Class to test functionality of abilities by simply clicking
//	on the attached unit
//
// @Ken

// Change this to test different abilities on click; see switch in onClick()
#define ABILITY_TEST 1

#include "UseAbilityWhenClicked.h"
#include "ability\AbilityManager.h"
#include "kitten\K_GameObject.h"
#include "unit\Unit.h"
#include "kitten\InputManager.h"
#include "kitten\K_ComponentManager.h"
#include "kitten\K_GameObjectManager.h"

UseAbilityWhenClicked::UseAbilityWhenClicked()
	:
	m_bSelectingAbility(false)
{

}

UseAbilityWhenClicked::~UseAbilityWhenClicked()
{
	kitten::K_ComponentManager::getInstance()->destroyComponent(m_textBox);
}

void UseAbilityWhenClicked::start()
{
	Clickable::start();
	m_pSelectAbilityComp = m_attachedObject->getComponent<SelectAbility>();

	m_textBox = static_cast<puppy::TextBox*>(kitten::K_ComponentManager::getInstance()->createComponent("TextBoxAbilities"));
	m_textBox->setColor(1, 1, 1);
	m_textBox->setText("");

	// TextBox relies on attached GO Transform, so we need a new GO just for the TextBox
	// to prevent issues with the Transforms
	// Creating a GO inside a component feels wrong
	kitten::K_GameObject* textBox = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
	textBox->addComponent(m_textBox);
	textBox->getTransform().place2D(1000, 600);
}

void UseAbilityWhenClicked::update()
{
	if (m_bSelectingAbility)
	{		
		m_textBox->setText("1: Manipulate Tile \n 2: Summon Unit");
		if (input::InputManager::getInstance()->keyDown('1') || input::InputManager::getInstance()->keyDown('1'))
		{
			m_pSelectAbilityComp->useAbility(SelectAbility::AbilityType::Manipulate_Tile);
			m_bSelectingAbility = false;
		}
		else if (input::InputManager::getInstance()->keyDown('2') || input::InputManager::getInstance()->keyDown('2'))
		{
			m_pSelectAbilityComp->useAbility(SelectAbility::AbilityType::Summon_Unit);
			m_bSelectingAbility = false;
		}
	}
	else
	{
		m_textBox->setText("");
	}
}

void UseAbilityWhenClicked::onClick()
{
	m_bSelectingAbility = true;

	//ability::AbilityInfoPackage* info = new ability::AbilityInfoPackage();
	//unit::Unit* unit = m_attachedObject->getComponent<unit::Unit>();
	//switch (ABILITY_TEST)
	//{
	//	case 0: // Highlight tiles that can be manipulated, for testing, do all
	//	{			
	//		for (int x = 0; x < 15; x++)
	//		{
	//			for (int z = 0; z < 15; z++)
	//			{
	//				info->m_targetTiles.push_back(std::make_pair(x, z));
	//			}
	//		}
	//		info->m_source = unit;

	//		ability::AbilityManager::getInstance()->useAbility(MANIPULATE_TILE_ABILITY, info);
	//		break;
	//	}
	//	case 1: // Testing SummonUnit ability
	//	{
	//		kitten::Transform& transform = m_attachedObject->getTransform();
	//		float unitOffsetX = 0.5f;
	//		glm::vec3 pos = transform.getTranslation();

	//		// @TODO
	//		// Need a better way to access tiles, current implementation assumes tiles based on 
	//		// position of the unit
	//		if (pos.x + unitOffsetX - 1 >= 0)
	//		{
	//			info->m_targetTiles.push_back(std::make_pair(pos.x + unitOffsetX - 1, pos.z));
	//			printf("1pushed tile %f, %f\n", pos.x + unitOffsetX - 1, pos.z);
	//		}
	//		if (pos.x + unitOffsetX + 1 < 15)
	//		{
	//			info->m_targetTiles.push_back(std::make_pair(pos.x + unitOffsetX + 1, pos.z));
	//			printf("2pushed tile %f, %f\n", pos.x + unitOffsetX + 1, pos.z);
	//		}
	//		if (pos.z - 1 >= 0)
	//		{
	//			info->m_targetTiles.push_back(std::make_pair(pos.x + unitOffsetX, pos.z - 1));
	//			printf("3pushed tile %f, %f\n", pos.x + unitOffsetX, pos.z - 1);
	//		}
	//		if (pos.z + 1 < 15)
	//		{
	//			info->m_targetTiles.push_back(std::make_pair(pos.x + unitOffsetX, pos.z + 1));
	//			printf("4pushed tile %f, %f\n", pos.x + unitOffsetX, pos.z + 1);
	//		}
	//		info->m_source = unit;
	//		ability::AbilityManager::getInstance()->useAbility(SUMMON_UNIT, info);
	//		break;
	//	}
	//}
}