#include "kitten/K_GameObject.h"
#include "unit/UnitData.h"

#include <string>

namespace kibble {
	class DataParserFactory {
	public:
		virtual kitten::K_GameObject* getGameObject(std::string filename) = 0;
		virtual UnitData* getUnit(std::string filename) = 0;
	};
}