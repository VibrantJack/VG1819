#pragma once
#include "unit/UnitCommon.h"

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
