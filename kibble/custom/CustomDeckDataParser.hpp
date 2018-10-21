#include "kibble/DeckDataParser.hpp"
class CustomDeckDataParser : public kibble::DeckDataParser {
	DeckData* getDeckData(const std::string& p_filename);
	void saveDeckData(DeckData* p_deck, const std::string& p_filename);
};

