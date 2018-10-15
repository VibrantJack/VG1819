#include "components\PowerTracker.h"
#include "kitten\K_ComponentManager.h"
#include "kitten\K_GameObjectManager.h"


PowerTracker::PowerTracker()
	:
	m_iMaxPower(4),
	m_iCurrentPower(4)
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Manipulate_Tile,
		this,
		std::bind(&PowerTracker::increaseMaxPowerEvent, this, std::placeholders::_1, std::placeholders::_2));
}

PowerTracker::~PowerTracker()
{
	kitten::K_ComponentManager::getInstance()->destroyComponent(m_textBox);
}

void PowerTracker::start()
{
	m_textBox = static_cast<puppy::TextBox*>(kitten::K_ComponentManager::getInstance()->createComponent("TextBox"));
	m_textBox->setColor(1, 1, 1);

	// TextBox relies on attached GO Transform, so we need a new GO just for the TextBox
	// to prevent issues with the Transforms
	// Creating a GO inside a component feels wrong
	kitten::K_GameObject* textBox = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
	textBox->addComponent(m_textBox);
	textBox->getTransform().place2D(800, 50);
}

void PowerTracker::update()
{
	m_textBox->setText("Max Power: " + std::to_string(m_iMaxPower) + " Current Power: " + std::to_string(getCurrentPower()));
}

void PowerTracker::increaseMaxPower(int p_iAmount)
{
	m_iMaxPower += p_iAmount;
}

void PowerTracker::increaseMaxPowerEvent(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	m_iMaxPower += p_data->getInt(MANIPULATE_TILE_KEY);
	resetCurrent(); // Maybe shouldn't be called here?
}

bool PowerTracker::summonUnitCost(int p_iCost)
{
	if ((m_iCurrentPower - p_iCost) >= 0)
	{
		m_iCurrentPower -= p_iCost;
		return true;
	}

	return false;
}

void PowerTracker::resetCurrent()
{
	m_iCurrentPower = m_iMaxPower;
}

int PowerTracker::getMaxPower()
{
	return m_iMaxPower;
}

int PowerTracker::getCurrentPower()
{
	return m_iCurrentPower;
}