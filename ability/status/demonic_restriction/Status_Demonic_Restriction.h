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
	};

	class Status_DR_Eternal_Eye : public Status_Demonic_Restriction
	{
	public:
		Status_DR_Eternal_Eye();
		Status* clone() const { return new Status_DR_Eternal_Eye(*this); };
		void restrictionOn();
		void restrictionOff();
	};
}