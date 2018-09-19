#pragma once
#include "kibble/GameObjectDataParser.hpp"

namespace kibble {
	class JSONGameObjectDataParser : public kibble::GameObjectDataParser {
	public:
		kitten::K_GameObject* getGameObject(const std::string& p_filename);
	};
}