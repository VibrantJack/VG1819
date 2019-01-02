#include "DeckComponent.hpp"
#include "DeckInitializingComponent.h"
#include <random>
#include <chrono> 
#include <algorithm>
#include <climits>
#include "kibble/databank/databank.hpp"

std::default_random_engine RNGzuz(std::random_device{}());// our holy lord, determiner of fate

DeckComponent::~DeckComponent() {
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Shuffle_Deck, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Discard_Card, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Draw_Card, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Add_Card, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Peek_Card, this);
}

void DeckComponent::start() {
	// Set up Events
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Shuffle_Deck,
		this,
		std::bind(&DeckComponent::shuffleEventReceiver, this, std::placeholders::_1, std::placeholders::_2));
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Discard_Card,
		this,
		std::bind(&DeckComponent::discardEventReceiver, this, std::placeholders::_1, std::placeholders::_2));
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Draw_Card,
		this,
		std::bind(&DeckComponent::drawEventReceiver, this, std::placeholders::_1, std::placeholders::_2));
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Add_Card,
		this,
		std::bind(&DeckComponent::addEventReceiver, this, std::placeholders::_1, std::placeholders::_2));
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Peek_Card,
		this,
		std::bind(&DeckComponent::peekEventReceiver, this, std::placeholders::_1, std::placeholders::_2));

	// Set up Parameters
	if (DeckInitializingComponent::getActiveInstance() == nullptr || DeckInitializingComponent::getActiveInstance()->getDeckId() < 0) {
		this->m_deckSource = kibble::getDeckDataFromId(0);
		this->m_playerID = 0;
	}
	else
	{
		this->m_deckSource = DeckInitializingComponent::getActiveInstance()->getDeckData();
		this->m_playerID = DeckInitializingComponent::getActiveInstance()->getPlayerId();
	}

	// Set up Pool
	this->m_cardPool.reserve(m_deckSource->totalCardCount);
	for (std::pair<int, int> card : m_deckSource->cards) {
		this->m_cardPool.resize(m_cardPool.size() + card.second, card.first); // expand it by repetition, and value set by index of card
	}

	// Shuffle the pool
	std::shuffle(m_cardPool.begin(),m_cardPool.end(),RNGzuz);

}

void DeckComponent::shuffleEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data) {
	if (p_data->getInt(PLAYER_ID) == m_playerID) {
		shuffle();
	}
}
void DeckComponent::discardEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data) {
	if (p_data->getInt(PLAYER_ID) == m_playerID) {
		discard(p_data->getInt(CARD_COUNT));
	}
}
void DeckComponent::drawEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data) {
	if (p_data->getInt(PLAYER_ID) == m_playerID) {
		draw(p_data->getInt(CARD_COUNT));
	}
}
void DeckComponent::peekEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data) {
	if (p_data->getInt(PLAYER_ID) == m_playerID) {
		peek(p_data->getInt(CARD_COUNT));
	}
}
void DeckComponent::addEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data) {
	if (p_data->getInt(PLAYER_ID) == m_playerID) {
		addTop(p_data->getInt(CARD_ID));
	}
}

void DeckComponent::shuffle() {
	std::shuffle(m_cardPool.begin(), m_cardPool.end(), RNGzuz);
}
void DeckComponent::draw(int p_topNum) {
	if (m_cardPool.empty()) {
		informEmptyDeck();
		return;
	}

	kitten::Event* eventData = new kitten::Event(kitten::Event::EventType::Card_Drawn);
	eventData->putInt(PLAYER_ID, m_playerID);
	int countLookOver = std::min(p_topNum,(int)m_cardPool.size());
	eventData->putInt(CARD_COUNT, countLookOver);

	for (int i = 0; i < countLookOver; ++i) {
		eventData->putInt(CARD_ID + std::to_string(i), m_cardPool.back());
		m_cardPool.pop_back();
	}
	kitten::EventManager::getInstance()->queueEvent(
		kitten::Event::EventType::Card_Drawn,
		eventData
	);
}
void DeckComponent::discard(int p_topNum) {
	if (m_cardPool.empty()) {
		informEmptyDeck();
		return;
	}

	kitten::Event* eventData = new kitten::Event(kitten::Event::EventType::Card_Discarded);
	eventData->putInt(PLAYER_ID, m_playerID);
	int countLookOver = std::min(p_topNum, (int)m_cardPool.size());
	eventData->putInt(CARD_COUNT, countLookOver);

	for (int i = 0; i < countLookOver; ++i) {
		eventData->putInt(CARD_ID + std::to_string(i), m_cardPool.back());
		m_cardPool.pop_back();
	}

	kitten::EventManager::getInstance()->queueEvent(
		kitten::Event::EventType::Card_Discarded,
		eventData
	);
}
void DeckComponent::addTop(int p_cardIndex) {
	m_cardPool.push_back(p_cardIndex);
}
void DeckComponent::peek(int p_topNum) {
	if (m_cardPool.empty()) {
		informEmptyDeck();
		return;
	}

	kitten::Event* eventData = new kitten::Event(kitten::Event::EventType::Card_Peeked);
	eventData->putInt(PLAYER_ID, m_playerID);
	int countLookOver = std::min(p_topNum, (int)m_cardPool.size());
	eventData->putInt(CARD_COUNT, countLookOver);

	for (auto i = 0; i < countLookOver; ++i) {
		eventData->putInt(CARD_ID + std::to_string(i), *(m_cardPool.rbegin()+countLookOver));
	}

	kitten::EventManager::getInstance()->queueEvent(
		kitten::Event::EventType::Card_Peeked,
		eventData
	);

}

void DeckComponent::informEmptyDeck() {
	kitten::Event* eventData = new kitten::Event(kitten::Event::EventType::Deck_Empty);
	eventData->putInt(PLAYER_ID, m_playerID);
	kitten::EventManager::getInstance()->queueEvent(
		kitten::Event::EventType::Deck_Empty,
		eventData
	);
}


void DeckComponent::onDisabled() {
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Shuffle_Deck, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Discard_Card, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Draw_Card, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Add_Card, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Peek_Card, this);
}
void DeckComponent::onEnabled() {
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Shuffle_Deck,
		this,
		std::bind(&DeckComponent::shuffleEventReceiver, this, std::placeholders::_1, std::placeholders::_2));
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Discard_Card,
		this,
		std::bind(&DeckComponent::discardEventReceiver, this, std::placeholders::_1, std::placeholders::_2));
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Draw_Card,
		this,
		std::bind(&DeckComponent::drawEventReceiver, this, std::placeholders::_1, std::placeholders::_2));
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Add_Card,
		this,
		std::bind(&DeckComponent::addEventReceiver, this, std::placeholders::_1, std::placeholders::_2));
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Peek_Card,
		this,
		std::bind(&DeckComponent::peekEventReceiver, this, std::placeholders::_1, std::placeholders::_2));
}