#include "Status_Demonic_Restriction.h"
#include "board/tile/TileInfo.h"

namespace ability
{
	Status_Demonic_Restriction::Status_Demonic_Restriction() : Status::Status()
	{
		m_Id = STATUS_DEMONIC_RESTRICTION;
		addTimePoint(TimePointEvent::New_Tile);
	}

	int Status_Demonic_Restriction::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent * p_event)
	{
		kitten::K_GameObject* tile = p_event->getGameObject("tile");
		TileInfo* info = tile->getComponent<TileInfo>();

		bool onDP = info->isDemonicPresence();
		if (onDP)
			restrictionOff();
		else
			restrictionOn();

		return 0;
	}
}


