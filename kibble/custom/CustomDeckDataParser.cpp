#include "CustomDeckDataParser.hpp"
#include "kibble/databank/databank.hpp"
#include "unit/Unit.h"
#include <iomanip>
#include <fstream>
DeckData* CustomDeckDataParser::getDeckData(const std::string& p_filename) {
	std::ifstream input("data/saved/"+p_filename);
	if (input.is_open()) {
		DeckData* data = new DeckData();
		data->filename = p_filename;
		std::getline(input, data->name); // Get Deck Name
		input >> data->commanderID; // Get Deck Commander

		int cardIndex, cardCount;
		while (input >> cardIndex >> cardCount) { // Get unit index and count
			data->cards.push_back(std::pair<int,int>(cardIndex, cardCount));
			data->totalCardCount += cardCount;
		}

		input.close();
		return data;
	}
	else {
		throw std::exception("Something went wrong, file can't be opened."); // check if filename is correct. Or if this file exists.
		return nullptr;
	}
}

void CustomDeckDataParser::saveDeckData(DeckData* p_deck, const std::string& p_filename) {
	std::ofstream output("data/saved/" + p_filename);
	if (output.is_open()) {
		output << *p_deck;

		output.close();
	}
	else {
		throw std::exception("Something went wrong, file can't be opened."); // check if filename is correct. Or if this file exists.
		return;
	}
}


std::ostream &operator<<(std::ostream &outputStream, const DeckData &deck) {
	outputStream << std::setw(8) << deck.name << std::endl
		<< "Commander: " << kibble::getUnitFromId(deck.commanderID)->m_name << std::endl
		<< std::setw(8) << "index" << std::setw(8) << "count" << "  name" << std::endl;
	auto it = deck.cards.begin();

	while (it != deck.cards.end()) {
		outputStream << std::setw(8) << it->first << std::setw(8) << it->second << " " << kibble::getUnitFromId(it->first)->m_name << std::endl;
		it++;
	}
	return outputStream;
}

std::ofstream &operator<<(std::ofstream &outputStream, const DeckData &deck) {
	outputStream << deck.name << std::endl << deck.commanderID << std::endl;
	auto it = deck.cards.begin();

	while (it != deck.cards.end()) {
		outputStream << it->first << " " << it->second << std::endl;
		it++;
	}
	return outputStream;
}