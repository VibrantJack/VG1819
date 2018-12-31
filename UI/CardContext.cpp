#include "UI\CardContext.h"
#include "kitten\K_GameObjectManager.h"
#include "UI\UIObject.h"
// Only for testing, using a static unit
#include "kibble\databank\databank.hpp"
#include "kitten\InputManager.h"

#define NAME_X 38.0f
#define NAME_Y 377.0f

#define TAGS_X 38.0f
#define TAGS_Y 350.0f

#define COST_X 220.0f
#define COST_Y 385.0f

#define HP_X 80.0f
#define HP_Y 170.0f

#define MV_X 136.0f
#define MV_Y 170.0f

#define IN_X 200.0f
#define IN_Y 170.0f

#define ABILITIES_X 20.0f
#define ABILITIES_Y 138.0f

#define LINE_HEIGHT 12.0f
#define LINE_MAX_CHAR_LENGTH 36.0f

CardContext::CardContext()
{

}

CardContext::~CardContext()
{

}

void CardContext::start()
{
	ClickableUI::start();

	kitten::K_GameObjectManager* gom = kitten::K_GameObjectManager::getInstance();
	m_cardTexture = gom->createNewGameObject("card_context_texture.json");

	m_nameBox = gom->createNewGameObject("card_context_textbox.json")->getComponent<puppy::TextBox>();

	m_tagsBox = gom->createNewGameObject("card_context_textbox.json")->getComponent<puppy::TextBox>();
	m_tagsBox->setFont(puppy::FontTable::getInstance()->getFont("../fonts/nsimsun_12pt.fnt"));

	m_hpBox = gom->createNewGameObject("card_context_textbox.json")->getComponent<puppy::TextBox>();
	m_hpBox->setAlignment(puppy::TextBox::center);

	m_mvBox = gom->createNewGameObject("card_context_textbox.json")->getComponent<puppy::TextBox>();
	m_mvBox->setAlignment(puppy::TextBox::center);

	m_initiativeBox = gom->createNewGameObject("card_context_textbox.json")->getComponent<puppy::TextBox>();
	m_initiativeBox->setAlignment(puppy::TextBox::center);

	m_costBox = gom->createNewGameObject("card_context_textbox.json")->getComponent<puppy::TextBox>();
	m_costBox->setFont(puppy::FontTable::getInstance()->getFont("../fonts/nsimsun_32pt.fnt"));
	m_costBox->setAlignment(puppy::TextBox::center);

	float centerOffset = m_nameBox->getBoxWidth() / 2;
	glm::vec3 contextPos = m_cardTexture->getTransform().getTranslation();
	m_nameBox->getTransform().place(NAME_X + contextPos.x, NAME_Y + contextPos.y, 0.01f);
	m_tagsBox->getTransform().place(TAGS_X + contextPos.x, TAGS_Y + contextPos.y, 0.01f);
	m_hpBox->getTransform().place(HP_X + contextPos.x - centerOffset, HP_Y + contextPos.y, 0.01f);
	m_mvBox->getTransform().place(MV_X + contextPos.x - centerOffset, MV_Y + contextPos.y, 0.01f);
	m_initiativeBox->getTransform().place(IN_X + contextPos.x - centerOffset, IN_Y + contextPos.y, 0.01f);
	m_costBox->getTransform().place(COST_X + contextPos.x - centerOffset, COST_Y + contextPos.y, 0.01f);

	// Testing
	setUnit(kibble::getUnitFromId(13));

	setEnabled(false);
}

void CardContext::setUnit(unit::Unit* p_unit)
{
	if (p_unit != m_unitData)
	{
		m_unitData = p_unit;
		updateUnitData();
	}
}

void CardContext::update()
{
	input::InputManager* inputMan = input::InputManager::getInstance();
	if (inputMan->keyDown('B') && !inputMan->keyDownLast('B'))
	{
		setUnit(kibble::getUnitFromId(m_unitId));

		m_unitId = (m_unitId + 1) % 15;
		if (m_unitId == 0 || m_unitId == 6)
			m_unitId++;
	}
}

void CardContext::updateUnitData()
{
	m_nameBox->setText(m_unitData->m_name);

	std::string tags = "";
	auto it = m_unitData->m_tags.begin();
	for (; it != m_unitData->m_tags.end(); ++it)
	{
		tags += *it + ", ";
	}
	m_tagsBox->setText(tags.substr(0, tags.length() - 2));

	m_hpBox->setText(std::to_string(m_unitData->m_attributes[UNIT_HP]));

	m_mvBox->setText(std::to_string(m_unitData->m_attributes[UNIT_MV]));

	m_initiativeBox->setText(std::to_string(m_unitData->m_attributes[UNIT_IN]));

	m_costBox->setText(std::to_string(m_unitData->m_attributes[UNIT_COST]));


	// Ability Info TextBoxes
	// Destroy the previous TextBoxes and clear the list
	auto abilityEnd = m_abilityList.cend();
	for (auto it = m_abilityList.cbegin(); it != abilityEnd; ++it)
	{
		kitten::K_GameObjectManager::getInstance()->destroyGameObject(&(*it)->getGameObject());
	}
	m_abilityList.clear();

	// Loop through the ability list
	// Create a TextBox for the ability name + stats and a TextBox for the ability description
	// Trying to use a max of 3 lines for each ability + description,
	// otherwise we won't be able to fit all the details on the card
	int row = 0;
	glm::vec3 contextPos = m_cardTexture->getTransform().getTranslation();
	for (auto it : m_unitData->m_ADList)
	{
		puppy::TextBox* abilityText = kitten::K_GameObjectManager::getInstance()->createNewGameObject("card_context_textbox.json")->getComponent<puppy::TextBox>();
		abilityText->setFont(puppy::FontTable::getInstance()->getFont("../fonts/nsimsun_12pt.fnt"));
		abilityText->setColor(0.89f, 0.82f, 0.55f);
		abilityText->getTransform().place(ABILITIES_X + contextPos.x, ABILITIES_Y + contextPos.y - (row * LINE_HEIGHT), 0.01f);

		std::string abilityDesc = "";
		unit::AbilityDescription* ad = it.second;

		int lv = ad->m_intValue[UNIT_LV];
		if (lv > 0)
			abilityDesc += "LV:" + std::to_string(lv) + " ";

		std::string abilityName = it.first;
		abilityDesc += abilityName + ":";

		int power = ad->m_intValue[UNIT_POWER];
		if (power > 0)
			abilityDesc += " Power:" + std::to_string(power);

		int cd = ad->m_intValue[UNIT_CD];
		if (cd > 0)
			abilityDesc += " CD:" + std::to_string(cd);

		int ct = ad->m_intValue[UNIT_CT];
		if (ct > 0)
			abilityDesc += " CT:" + std::to_string(ct);
				
		abilityText->setText(abilityDesc);
		m_abilityList.push_back(abilityText);
		row += std::ceil(abilityDesc.length() / LINE_MAX_CHAR_LENGTH); // Determines how many rows have been used by the text that's been set

		// Creating a new TextBox for the description
		std::string description = ad->m_stringValue[UNIT_ABILITY_DESCRIPTION];
		if (description.length() > 0)
		{
			abilityText = kitten::K_GameObjectManager::getInstance()->createNewGameObject("card_context_textbox.json")->getComponent<puppy::TextBox>();
			abilityText->setFont(puppy::FontTable::getInstance()->getFont("../fonts/nsimsun_12pt.fnt"));
			abilityText->getTransform().place(ABILITIES_X + contextPos.x, ABILITIES_Y + contextPos.y - (row * LINE_HEIGHT), 0.01f);
			abilityText->setText(description);
			m_abilityList.push_back(abilityText);
			row += std::ceil(description.length() / LINE_MAX_CHAR_LENGTH);
		}
	}

	// Status Info TextBoxes
	// Similar idea to ability TextBoxes, clear the list and loop through status
	// TODO: Get the ability changes on level up into the unit .json files so we can get them here 
	// to display. ex. LV3 Archer's Quick Shoot can shoot 3 times instead of 2
	auto statusEnd = m_statusList.cend();
	for (auto it = m_statusList.cbegin(); it != statusEnd; ++it)
	{
		kitten::K_GameObjectManager::getInstance()->destroyGameObject(&(*it)->getGameObject());
	}
	m_statusList.clear();

	unit::StatusContainer* statusContainer = m_unitData->getStatusContainer();
	for (auto it : statusContainer->m_statusList)
	{
		puppy::TextBox* statusText = kitten::K_GameObjectManager::getInstance()->createNewGameObject("card_context_textbox.json")->getComponent<puppy::TextBox>();
		statusText->setFont(puppy::FontTable::getInstance()->getFont("../fonts/nsimsun_12pt.fnt"));
		statusText->setColor(0.0f, 0.0f, 0.0f);
		statusText->getTransform().place(ABILITIES_X + contextPos.x, ABILITIES_Y + contextPos.y - (row * 12.0f), 0.01f);

		std::string statusDesc = "";
		std::unordered_map<std::string, int> attributes = it->getAttributeChanges();

		int lv = it->getLV();
		if (lv > 0)
			statusDesc += "LV:" + std::to_string(lv);
		
		int hp = attributes[UNIT_HP];
		if (hp > 0)
			statusDesc += " HP+" + std::to_string(hp);

		int in = attributes[UNIT_IN];
		if (in > 0)
			statusDesc += " IN+" + std::to_string(in);

		int mv = attributes[UNIT_MV];
		if (mv > 0)
			statusDesc += " MV+" + std::to_string(mv);

		statusText->setText(statusDesc);
		m_statusList.push_back(statusText);
		row += std::ceil(statusDesc.length() / LINE_MAX_CHAR_LENGTH);
	}
}

void CardContext::onHoverStart()
{
	setEnabled(true);
}

void CardContext::onHoverEnd()
{
	setEnabled(false);
}

void CardContext::onEnabled()
{
	m_cardTexture->setEnabled(true);
	m_nameBox->setEnabled(true);
	m_tagsBox->setEnabled(true);
	m_hpBox->setEnabled(true);
	m_mvBox->setEnabled(true);
	m_initiativeBox->setEnabled(true);
	m_costBox->setEnabled(true);

	auto abilityEnd = m_abilityList.cend();
	for (auto it = m_abilityList.cbegin(); it != abilityEnd; ++it)
	{
		(*it)->setEnabled(true);
	}

	auto statusEnd = m_statusList.cend();
	for (auto it = m_statusList.cbegin(); it != statusEnd; ++it)
	{
		(*it)->setEnabled(true);
	}
}

void CardContext::onDisabled()
{
	m_cardTexture->setEnabled(false);
	m_nameBox->setEnabled(false);
	m_tagsBox->setEnabled(false);
	m_hpBox->setEnabled(false);
	m_mvBox->setEnabled(false);
	m_initiativeBox->setEnabled(false);
	m_costBox->setEnabled(false);

	auto abilityEnd = m_abilityList.cend();
	for (auto it = m_abilityList.cbegin(); it != abilityEnd; ++it)
	{
		(*it)->setEnabled(false);
	}

	auto statusEnd = m_statusList.cend();
	for (auto it = m_statusList.cbegin(); it != statusEnd; ++it)
	{
		(*it)->setEnabled(false);
	}
}