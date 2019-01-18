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

#define PORTRAIT_X 52.0f
#define PORTRAIT_Y 180.0f

CardContext::CardContext()
{

}

CardContext::~CardContext()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Update_Card_Context_By_ID, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Update_Card_Context_By_GO, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Card_Context_Set_Enabled, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Update_Card_Context_Attrib, this);
}

void CardContext::start()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Update_Card_Context_By_ID,
		this,
		std::bind(&CardContext::setUnitListener, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Update_Card_Context_By_GO,
		this,
		std::bind(&CardContext::setUnitListener, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Card_Context_Set_Enabled,
		this,
		std::bind(&CardContext::setEnabledListener, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Update_Card_Context_Attrib,
		this,
		std::bind(&CardContext::updateUnitAttributesListener, this, std::placeholders::_1, std::placeholders::_2));

	kitten::K_GameObjectManager* gom = kitten::K_GameObjectManager::getInstance();
	// Cannot set these as children as they won't display
	m_cardTexture = gom->createNewGameObject("UI/card_context/card_context_texture.json");
	m_unitPortrait = gom->createNewGameObject("UI/card_context/card_context_portrait.json")->getComponent<userinterface::UIObject>();

	m_nameBox = gom->createNewGameObject("UI/card_context/card_context_name_textbox.json")->getComponent<puppy::TextBox>();
	m_nameBox->getGameObject().getTransform().setIgnoreParent(false);
	m_nameBox->getGameObject().getTransform().setParent(&m_attachedObject->getTransform());

	m_tagsBox = gom->createNewGameObject("UI/card_context/card_context_tags_textbox.json")->getComponent<puppy::TextBox>();
	m_tagsBox->getGameObject().getTransform().setIgnoreParent(false);
	m_tagsBox->getGameObject().getTransform().setParent(&m_attachedObject->getTransform());

	m_hpBox = gom->createNewGameObject("UI/card_context/card_context_hp_textbox.json")->getComponent<puppy::TextBox>();
	m_hpBox->getGameObject().getTransform().setIgnoreParent(false);
	m_hpBox->getGameObject().getTransform().setParent(&m_attachedObject->getTransform());

	m_mvBox = gom->createNewGameObject("UI/card_context/card_context_mv_textbox.json")->getComponent<puppy::TextBox>();
	m_mvBox->getGameObject().getTransform().setIgnoreParent(false);
	m_mvBox->getGameObject().getTransform().setParent(&m_attachedObject->getTransform());

	m_initiativeBox = gom->createNewGameObject("UI/card_context/card_context_in_textbox.json")->getComponent<puppy::TextBox>();
	m_initiativeBox->getGameObject().getTransform().setIgnoreParent(false);
	m_initiativeBox->getGameObject().getTransform().setParent(&m_attachedObject->getTransform());

	m_costBox = gom->createNewGameObject("UI/card_context/card_context_cost_textbox.json")->getComponent<puppy::TextBox>();
	m_costBox->getGameObject().getTransform().setIgnoreParent(false);
	m_costBox->getGameObject().getTransform().setParent(&m_attachedObject->getTransform());

	// Testing
	setUnit(kibble::getUnitFromId(13));

	m_attachedObject->setEnabled(false);
}

void CardContext::setUnit(unit::Unit* p_unit)
{
	if (p_unit != m_unitData && p_unit != nullptr)
	{
		m_unitData = p_unit;
		m_unitPortrait->setTexture(p_unit->getPortraitTexturePath().c_str());
		updateUnitData();
	}
}

void CardContext::setUnitListener(kitten::Event::EventType p_type, kitten::Event* p_event)
{
	if (p_type == kitten::Event::Update_Card_Context_By_GO)
	{
		kitten::K_GameObject* unitGO = p_event->getGameObj(UPDATE_CARD_CONTEXT_KEY);
		if (unitGO != nullptr)
		{
			unit::Unit* unit = unitGO->getComponent<unit::Unit>();
			setUnit(unit);
		}
	}
	else if (p_type == kitten::Event::Update_Card_Context_By_ID)
	{
		setUnit(kibble::getUnitFromId(p_event->getInt(UPDATE_CARD_CONTEXT_KEY)));
	}
}

void CardContext::updateUnitAttributesListener(kitten::Event::EventType p_type, kitten::Event* p_event)
{
	updateUnitAttributes();
}

// For testing only, changes the unit on the hovered card by pressing the B key
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
	updateUnitAttributes();

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
	float padding = 0.0f;
	glm::vec3 contextPos = getTransform().getTranslation();
	for (auto it : m_unitData->m_ADList)
	{
		puppy::TextBox* abilityText = kitten::K_GameObjectManager::getInstance()->createNewGameObject("UI/card_context/card_context_textbox.json")->getComponent<puppy::TextBox>();
		abilityText->setFont(puppy::FontTable::getInstance()->getFont("../fonts/nsimsun_12pt.fnt"));
		abilityText->setColor(0.89f, 0.82f, 0.55f);
		abilityText->getTransform().place(ABILITIES_X, ABILITIES_Y - (row * LINE_HEIGHT) - padding, 0.01f);
		abilityText->getTransform().setIgnoreParent(false);
		abilityText->getTransform().setParent(&m_attachedObject->getTransform());

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
			abilityText = kitten::K_GameObjectManager::getInstance()->createNewGameObject("UI/card_context/card_context_textbox.json")->getComponent<puppy::TextBox>();
			abilityText->setFont(puppy::FontTable::getInstance()->getFont("../fonts/nsimsun_12pt.fnt"));
			abilityText->getTransform().place(ABILITIES_X, ABILITIES_Y - (row * LINE_HEIGHT) - padding, 0.01f);
			abilityText->getTransform().setIgnoreParent(false);
			abilityText->getTransform().setParent(&m_attachedObject->getTransform());
			abilityText->setText(description);
			m_abilityList.push_back(abilityText);
			row += std::ceil(description.length() / LINE_MAX_CHAR_LENGTH);
		}
		padding += 4.0f;
	}
	// Status Info TextBoxes
	// Similar idea to ability TextBoxes, clear the list and loop through status
	auto statusEnd = m_statusList.cend();
	for (auto it = m_statusList.cbegin(); it != statusEnd; ++it)
	{
		kitten::K_GameObjectManager::getInstance()->destroyGameObject(&(*it)->getGameObject());
	}
	m_statusList.clear();

	unit::StatusContainer* statusContainer = m_unitData->getStatusContainer();
	for (auto it : statusContainer->m_statusList)
	{
		puppy::TextBox* statusText = kitten::K_GameObjectManager::getInstance()->createNewGameObject("UI/card_context/card_context_textbox.json")->getComponent<puppy::TextBox>();
		statusText->setFont(puppy::FontTable::getInstance()->getFont("../fonts/nsimsun_12pt.fnt"));
		statusText->setColor(0.0f, 0.0f, 0.0f);
		statusText->getTransform().place(ABILITIES_X, ABILITIES_Y - (row * LINE_HEIGHT) - padding, 0.01f);
		statusText->getTransform().setIgnoreParent(false);
		statusText->getTransform().setParent(&m_attachedObject->getTransform());

		std::string statusDesc = "";
		std::unordered_map<std::string, int> attributes = it->getAttributeChanges();

		int lv = it->getLV();
		if (lv > 0)
			statusDesc += "LV:" + std::to_string(lv);
		else
		{
			std::string name = it->getName();
			statusDesc += name + ":";
		}

		int hp = attributes[UNIT_HP];
		if (hp > 0)
			statusDesc += " HP+" + std::to_string(hp);

		int in = attributes[UNIT_IN];
		if (in > 0)
			statusDesc += " IN+" + std::to_string(in);

		int mv = attributes[UNIT_MV];
		if (mv > 0)
			statusDesc += " MV+" + std::to_string(mv);


		std::string description = it->getDescription();
		statusDesc += " "+description;

		statusText->setText(statusDesc);
		m_statusList.push_back(statusText);
		row += std::ceil(statusDesc.length() / LINE_MAX_CHAR_LENGTH);
	}
}

void CardContext::updateUnitAttributes()
{
	if (m_unitData->m_attributes[UNIT_HP] < 0)
	{
		setEnabled(false);
	}
	m_hpBox->setText(std::to_string(m_unitData->m_attributes[UNIT_HP]));
	m_mvBox->setText(std::to_string(m_unitData->m_attributes[UNIT_MV]));
	m_initiativeBox->setText(std::to_string(m_unitData->m_attributes[UNIT_IN]));
	m_costBox->setText(std::to_string(m_unitData->m_attributes[UNIT_COST]));

	setAttribTextColor(m_hpBox, UNIT_HP, UNIT_MAX_HP);
	setAttribTextColor(m_mvBox, UNIT_MV, UNIT_BASE_MV);
	setAttribTextColor(m_initiativeBox, UNIT_IN, UNIT_BASE_IN);
	setAttribTextColor(m_costBox, UNIT_COST, UNIT_BASE_COST);
}

void CardContext::setAttribTextColor(puppy::TextBox* p_textBox, const std::string& p_currAttrib, const std::string& p_baseAttrib)
{
	if (m_unitData->m_attributes[p_currAttrib] < m_unitData->m_attributes[p_baseAttrib])
	{
		p_textBox->setColor(1.0f, 0.0f, 0.0f);
	} 
	else if (m_unitData->m_attributes[p_currAttrib] > m_unitData->m_attributes[p_baseAttrib])
	{
		p_textBox->setColor(0.0f, 0.5f, 1.0f);
	} 
	else
	{
		p_textBox->setColor(1.0f, 1.0f, 1.0f);
	}
}

void CardContext::onEnabled()
{
	std::vector<kitten::Transform*> parentChildren = m_attachedObject->getTransform().getChildren();
	for (kitten::Transform* t : parentChildren)
	{
		t->getAttachedGameObject().setEnabled(true);
	}
	m_cardTexture->setEnabled(true);
	m_unitPortrait->setEnabled(true);
}

void CardContext::onDisabled()
{
	std::vector<kitten::Transform*> parentChildren = m_attachedObject->getTransform().getChildren();
	for (kitten::Transform* t : parentChildren)
	{
		t->getAttachedGameObject().setEnabled(true);
	}
	m_cardTexture->setEnabled(false);
	m_unitPortrait->setEnabled(false);
}

void CardContext::setEnabledListener(kitten::Event::EventType p_type, kitten::Event* p_event)
{
	m_attachedObject->setEnabled(p_event->getInt(CARD_CONTEXT_SET_ENABLED_KEY));
}