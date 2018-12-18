#pragma once
#include "ContextMenu.h"

namespace userinterface
{
	class CommanderContext : public ContextMenu
	{
	public:
		CommanderContext();
		~CommanderContext();
		void start() override;
	};
}
