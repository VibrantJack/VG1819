#include "DeckComponent.hpp"
#include <random>
#include <chrono> 
#include <algorithm>

std::default_random_engine RNGzuz(std::random_device{}());// our holy lord, determiner of fate

DeckComponent::DeckComponent(DeckData* p_data, int p_playerID) : m_deckSource(p_data), m_playerID(p_playerID) {
	m_cardPool.reserve(p_data->totalCardCount);
}
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

	// Set up Pool
	for (std::pair<int, int> card : m_deckSource->cards) {
		this->m_cardPool.resize(m_cardPool.size() + card.second, card.first); // expand it by repetition, and value set by index of card
	}

	// Shuffle the pool
	std::shuffle(m_cardPool.begin(),m_cardPool.end(),RNGzuz);

}

void DeckComponent::shuffleEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data) {
	if (p_data->getInt("playerID") == m_playerID) {
		shuffle();
	}
}
void DeckComponent::discardEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data) {
	if (p_data->getInt("playerID") == m_playerID) {
		discard(p_data->getInt("count"));
	}
}
void DeckComponent::drawEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data) {
	if (p_data->getInt("playerID") == m_playerID) {
		draw(p_data->getInt("count"));
	}
}
void DeckComponent::peekEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data) {
	if (p_data->getInt("playerID") == m_playerID) {
		peek(p_data->getInt("count"));
	}
}
void DeckComponent::addEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data) {
	if (p_data->getInt("playerID") == m_playerID) {
		addTop(p_data->getInt("cardID"));
	}
}

void DeckComponent::shuffle() {
	std::shuffle(m_cardPool.begin(), m_cardPool.end(), RNGzuz);
}
void DeckComponent::draw(int p_topNum) {
	for (int i = 0; i < p_topNum; i++) {
		if (m_cardPool.size() == 0) {
			informEmptyDeck();
			return;
		}

		kitten::Event* eventData = new kitten::Event(kitten::Event::EventType::Card_Drawn);
		eventData->putInt("playerID", m_playerID);
		eventData->putInt("cardID", m_cardPool.back());
		eventData->putInt("placement", i);
		m_cardPool.pop_back();
		kitten::EventManager::getInstance()->queueEvent(
			kitten::Event::EventType::Card_Drawn,
			eventData
		);
	}
}
void DeckComponent::discard(int p_topNum) {
	for (int i = 0; i < p_topNum; i++) {
		if (m_cardPool.size() == 0) {
			informEmptyDeck();
			return;
		}

		kitten::Event* eventData = new kitten::Event(kitten::Event::EventType::Card_Discarded);
		eventData->putInt("playerID", m_playerID);
		eventData->putInt("cardID", m_cardPool.back());
		eventData->putInt("placement", i);
		m_cardPool.pop_back();
		kitten::EventManager::getInstance()->queueEvent(
			kitten::Event::EventType::Card_Discarded,
			eventData
		);
	}
}
void DeckComponent::addTop(int p_cardIndex) {
	m_cardPool.push_back(p_cardIndex);
}
void DeckComponent::peek(int p_topNum) {
	for (int i = 0; i < p_topNum; i++) {
		if (m_cardPool.size() == 0) {
			return;
		}

		kitten::Event* eventData = new kitten::Event(kitten::Event::EventType::Card_Peeked);
		eventData->putInt("playerID", m_playerID);
		eventData->putInt("cardID", m_cardPool.back());
		eventData->putInt("placement", i);
		kitten::EventManager::getInstance()->queueEvent(
			kitten::Event::EventType::Card_Peeked,
			eventData
		);
	}
}

void DeckComponent::informEmptyDeck() {
	kitten::Event* eventData = new kitten::Event(kitten::Event::EventType::Deck_Empty);
	eventData->putInt("playerID", m_playerID);
	kitten::EventManager::getInstance()->queueEvent(
		kitten::Event::EventType::Deck_Empty,
		eventData
	);
}