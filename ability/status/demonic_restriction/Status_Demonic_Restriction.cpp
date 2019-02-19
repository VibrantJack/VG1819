#include "Status_Demonic_Restriction.h"
#include "board/tile/TileInfo.h"

namespace ability
{
	Status_Demonic_Restriction::Status_Demonic_Restriction() : Status::Status()
	{
		m_name = "Demonic Restriction";
		m_Id = STATUS_DEMONIC_RESTRICTION;
		m_refreshTP = TimePointEvent::None;
		addTimePoint(TimePointEvent::New_Tile);
	}

	int Status_Demonic_Restriction::effect(const TimePointEvent::TPEventType& p_type, TimePointEvent* p_event)
	{
		if (p_type == TimePointEvent::New_Tile)
		{
			kitten::K_GameObject* tile = p_event->getGameObject("tile");
			TileInfo* info = tile->getComponent<TileInfo>();

			bool onDP = info->isDemonicPresence();
			if (m_restriction && onDP)//has restriction
			{
				m_restriction = false;//remove restriction
				restrictionOff();
			}
			else if (!m_restriction && !onDP)//no restriction
			{
				m_restriction = true;//add restriction
				restrictionOn();
			}
		}
		else if (p_type == m_refreshTP)
			refresh();

		return 0;
	}

	void Status_Demonic_Restriction::refreshOnTP(TimePointEvent::TPEventType p_type)
	{
		m_refreshTP = p_type;
		addTimePoint(p_type);
	}

	void Status_Demonic_Restriction::refresh()
	{
		if (m_restriction)//has restriction, then refresh it
		{
			restrictionOff();
			restrictionOn();
		}
	}
}


