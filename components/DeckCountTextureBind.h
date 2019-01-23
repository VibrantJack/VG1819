#pragma once 
#include "kitten/K_Component.h"
#include "kitten/event_system/Event.h"
#include <map>
#include <string>

class DeckCountTextureBind : public kitten::K_Component
{
protected:	
	int m_deckCount = 1000;
	std::map<int,std::string> m_texPairs;
	std::map<int,std::string>::reverse_iterator m_currentTexPair;
	void deckEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data);
public:
	void start();

	void addTexPair(int p_atCount, std::string p_tex);

	DeckCountTextureBind();
	~DeckCountTextureBind();
};