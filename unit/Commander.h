#pragma once
#include "unit/Unit.h"

//@Rock

namespace unit
{
	class Commander : public unit::Unit
	{
	public:
		Commander();
		~Commander();

		std::string m_porPath;
	};
}
