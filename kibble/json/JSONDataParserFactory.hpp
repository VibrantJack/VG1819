/*
Interface between the under belly of the parser and the actual game. 
*/
#include "kibble/DataParserFactory.hpp"

#include <string>

namespace kibble {
	class JSONDataParserFactory : public kibble::DataParserFactory {
	public:
		kitten::K_GameObject* getGameObject(std::string filename);
		Unit* getUnit(std::string filename);
	};
}