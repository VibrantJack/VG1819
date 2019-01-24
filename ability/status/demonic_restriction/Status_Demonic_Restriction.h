#pragma once
#include "ability/status/statusEvent/TimePointEvent.h"
#include "ability/status/Status.h"

namespace ability
{
	class Status_Demonic_Restriction : public Status
	{
	public:
		Status_Demonic_Restriction();
		virtual Status* clone() const = 0;
		virtual int effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent* p_event);
		virtual void restrictionOn() = 0;
		virtual void restrictionOff() = 0;
	protected:
		bool m_restriction = false;

		TimePointEvent::TPEventType m_refreshTP;

		void refreshOnTP(TimePointEvent::TPEventType p_type);
		void refresh();
	};

	class Status_DR_Eternal_Eye : public Status_Demonic_Restriction
	{
	public:
		Status_DR_Eternal_Eye();
		Status* clone() const { return new Status_DR_Eternal_Eye(*this); };
		void restrictionOn();
		void restrictionOff();
	};

	class Status_DR_Mud_Demon : public Status_Demonic_Restriction
	{
	public:
		Status_DR_Mud_Demon();
		Status* clone() const { return new Status_DR_Mud_Demon(*this); };
		void restrictionOn();
		void restrictionOff();
	private:
		int m_deltaMV;
	};
}