#pragma once
#include "DeckData.hpp"
#include <iostream>


namespace kibble {
	class DeckDataParser {
	public:
		virtual DeckData* getDeckData(const std::string& p_filename) = 0;
		virtual void saveDeckData(DeckData* p_deck, const std::string& p_filename) = 0;
	};
}

std::ostream &operator<<(std::ostream &outputStream, const DeckData &deck);
std::ofstream &operator<<(std::ofstream &outputStream, const DeckData &deck);