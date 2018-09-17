#pragma once
#include "kitten/K_Component.h"

#include <string>

namespace kibble {
	class ComponentDataParser {
	public:
		virtual kitten::K_Component* getComponentInternally() = 0;
	};
}