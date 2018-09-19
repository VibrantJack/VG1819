#pragma once
#include "kitten/K_Component.h"

#include <string>

namespace kibble {
	class ComponentDataParser {
	public:
		// Any necessary data has to be passed to this class through constructor when creating the concrete implementation
		virtual kitten::K_Component* getComponentInternally() = 0;
	};
}