#include "kitten/K_GameObject.h"
#include "unit/Unit.h"
#include <string>

namespace kibble {
	class DataParserFactory {
	public:
		virtual kitten::K_GameObject* getGameObject(std::string filename) = 0;
		virtual Unit* getUnit(std::string filename) = 0;
	};
}