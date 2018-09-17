#pragma once
#include "kitten/K_GameObject.h"

#include <string>

namespace kibble {
	class GameObjectDataParser {
	public:
		virtual kitten::K_GameObject* getGameObject(std::string filename) = 0;
	};
}