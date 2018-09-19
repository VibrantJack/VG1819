#pragma once
#include "kitten/K_GameObject.h"

#include <string>

namespace kibble {
	class GameObjectDataParser {
	public:
		// Make sure all concrete implementations get their object directly from the GameObjectManager
		virtual kitten::K_GameObject* getGameObject(const std::string& filename) = 0;
	};
}