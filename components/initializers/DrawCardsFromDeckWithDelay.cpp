#include "DrawCardsFromDeckWithDelay.h"
#include "kitten/event_system/EventManager.h"
#define TIME_DELAY_BETWEEN_DRAWS 0.5
#define TIME_DELAY_TILL_DRAW 0
#define START_GAME_CARD_COUNT 5

DrawCardsFromDeckWithDelay* instance = nullptr;

DrawCardsFromDeckWithDelay::DrawCardsFromDeckWithDelay()
{
	instance = this;
	this->m_delayBetweenDraws = TIME_DELAY_BETWEEN_DRAWS;
}

DrawCardsFromDeckWithDelay::~DrawCardsFromDeckWithDelay()
{
	instance = nullptr;
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Client_Commander_Loaded, this);
}

DrawCardsFromDeckWithDelay * DrawCardsFromDeckWithDelay::getActiveInstance()
{
	return instance;
}

void DrawCardsFromDeckWithDelay::setCardCountToDispense(unsigned int p_count)
{
	m_cardsToDispense = p_count;
	m_cardsDispensed = 0;
	this->setEnabled(true);
}

void DrawCardsFromDeckWithDelay::update()
{
	m_timeElapsed += m_time->getDeltaTime();
	if (m_timeElapsed > m_delayBetweenDraws) // if past delay
	{
		m_timeElapsed -= m_delayBetweenDraws;
		if (m_cardsDispensed >= m_cardsToDispense)
		{
			this->setEnabled(false);
			return;
		}
		m_cardsDispensed++;

		kitten::Event *e = new kitten::Event(kitten::Event::EventType::Draw_Card);// make a draw event
		e->putInt(PLAYER_ID, 0); // give it a player id, 0 being default TODO change this if ever needed. 0 signifies this side's instance player's id. any other should be any number other than 0 
		e->putInt(CARD_COUNT, 1); //tell it to draw 1 card
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Draw_Card, e); // Call the event
	}
}

void DrawCardsFromDeckWithDelay::start()
{
	m_time = kitten::K_Time::getInstance();
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Client_Commander_Loaded,
		this,
		std::bind(&setupNetworkGame, this, std::placeholders::_1, std::placeholders::_2));
}

void DrawCardsFromDeckWithDelay::setupNetworkGame(kitten::Event::EventType p_type, kitten::Event * p_event)
{
	setCardCountToDispense(START_GAME_CARD_COUNT);
	addDelayToStart(TIME_DELAY_TILL_DRAW);
}