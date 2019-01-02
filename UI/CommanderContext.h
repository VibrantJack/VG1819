#pragma once
#include "ContextMenu.h"
#include "unit\Unit.h"

namespace userinterface
{
	class CommanderContext : public ContextMenu
	{
	public:
		CommanderContext();
		~CommanderContext();
		void start() override;
		void attachCommander(unit::Unit* p_commanderToAttach);
	private:
		unit::Unit* m_attachedCommander;
	};
}
