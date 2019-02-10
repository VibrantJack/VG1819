#include "DrawCardOnClickUI.h"
#include "kitten/event_system/EventManager.h"
#include "UI/HandFrame.h"

#include <iostream>
void DrawCardOnClickUI::onClick() {
	if (userinterface::HandFrame::getActiveInstance()->getTotalCardsInHand() < 5) {
		kitten::Event *e = new kitten::Event(kitten::Event::EventType::Draw_Card);// make a draw event
		e->putInt(PLAYER_ID, 0); // give it a player id, 0 being default TODO change this if ever needed. 0 signifies this side's instance player's id. any other should be any number other than 0 
		e->putInt(CARD_COUNT, 1); //tell it to draw 1 card
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Draw_Card, e); // Call the event
	}
}