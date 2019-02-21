#include "components\PowerTracker.h"
#include "kitten\K_ComponentManager.h"
#include "kitten\K_GameObjectManager.h"
#include "puppy\Text\FontTable.h"

#define REGULAR_FONT "../fonts/nsimsun_38pt.fnt"
#define SMALL_FONT "../fonts/nsimsun_34pt.fnt"

PowerTracker::PowerTracker()
	:
	m_iMaxPower(0),
	m_iCurrentPower(0),
	m_textBox(nullptr)
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Manipulate_Tile,
		this,
		std::bind(&PowerTracker::increaseMaxPowerEvent, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Reset_Power,
		this,
		std::bind(&PowerTracker::resetEvent, this, std::placeholders::_1, std::placeholders::_2));

}

PowerTracker::~PowerTracker()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Manipulate_Tile, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Reset_Power, this);
	m_textBox = nullptr;
}

void PowerTracker::start()
{
	kitten::K_GameObject* powerIcon = kitten::K_GameObjectManager::getInstance()->createNewGameObject("UI/power_tracker/power_tracker_icon.json");
	kitten::K_GameObject* textBox = kitten::K_GameObjectManager::getInstance()->createNewGameObject("UI/power_tracker/power_tracker_textbox.json");
	textBox->getTransform().setIgnoreParent(false);
	textBox->getTransform().setParent(&powerIcon->getTransform());	
	m_textBox = textBox->getComponent<puppy::TextBox>();

	auto scale = powerIcon->getTransform().getScale();
	textBox->getTransform().place(0.0f, (scale.y / 2.0f) + 30.0f, 0.001);

	m_regularFont = puppy::FontTable::getInstance()->getFont(REGULAR_FONT);
	m_smallFont = puppy::FontTable::getInstance()->getFont(SMALL_FONT);
	m_currentFont = m_regularFont;

	updateTextBox();
}

void PowerTracker::updateTextBox()
{
	if (m_textBox != nullptr)
	{
		if (m_iMaxPower > 9 && m_currentFont != m_smallFont)
		{
			m_textBox->setFont(m_smallFont);
			m_currentFont = m_smallFont;
		}
		m_textBox->setText(std::to_string(getCurrentPower()) + "/" + std::to_string(m_iMaxPower));
	}
}

void PowerTracker::increaseMaxPower(int p_iAmount)
{
	m_iMaxPower += p_iAmount;
	updateTextBox();
}

void PowerTracker::increaseMaxPowerEvent(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	int power = p_data->getInt(MANIPULATE_TILE_KEY);
	m_iMaxPower += power;
	m_iCurrentPower += power;
	updateTextBox();
}

bool PowerTracker::summonUnitCost(int p_iCost)
{
	if ((m_iCurrentPower - p_iCost) >= 0)
	{
		m_iCurrentPower -= p_iCost;
		updateTextBox();
		return true;
	}

	return false;
}

void PowerTracker::resetCurrent()
{
	m_iCurrentPower = m_iMaxPower;
	updateTextBox();
}

void PowerTracker::resetEvent(kitten::Event::EventType p_type, kitten::Event * p_data)
{
	resetCurrent();
}

int PowerTracker::getMaxPower()
{
	return m_iMaxPower;
}

int PowerTracker::getCurrentPower()
{
	return m_iCurrentPower;
}


bool PowerTracker::changeCurrentPower(int p_iAmount)
{
	if ((m_iCurrentPower + p_iAmount) >= 0)
	{
		m_iCurrentPower += p_iAmount;
		updateTextBox();
		return true;
	}

	return false;
}