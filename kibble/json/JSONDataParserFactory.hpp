/*
Interface between the under belly of the parser and the actual game. 
*/
#include "kibble/DataParserFactory.hpp"
#include "kitten/K_GameObject.h"
#include "unit/UnitData.h"

#include <string>

namespace kibble {
	class JSONDataParserFactory : public kibble::DataParserFactory {
	public:
		kitten::K_GameObject* getGameObject(std::string filename);
		UnitData* getUnit(std::string filename);
	};
}