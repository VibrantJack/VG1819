#pragma once
#include "ability/status/statusEvent/TimePointEvent.h"
#include "ability/status/Status.h"

namespace ability
{
	class Status_LV : public Status
	{
		//this class handle the attribute change for all lv up status
	public:
		Status_LV();
		virtual Status* clone() const { return new Status_LV(*this); };
		virtual int effect() override;
		virtual int effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event);

	protected:
		void setLvUpAttributes(const std::string& p_attribute, const std::string& p_baseAttribute);
	};

	class Status_Priest_LV3 : public Status_LV
	{
		//this is trigger when preiest is lv3
	private:
		bool m_activate = false;
	public:
		Status_Priest_LV3();
		Status* clone() const { return new Status_Priest_LV3(*this); };
		int effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event);
	};

	class Status_Archer_LV3 : public Status_LV
	{
		//this is trigger when Archer is lv3
	public:
		Status_Archer_LV3();
		Status* clone() const { return new Status_Archer_LV3(*this); };

		int effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event);
	};

	class Status_Duelist_LV3 : public Status_LV
	{
		//this is trigger when Duelist is lv3
	public:
		Status_Duelist_LV3();
		Status* clone() const { return new Status_Duelist_LV3(*this); };

		int effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event);
	};

	class Status_Eternal_Eye_LV3 : public Status_LV
	{
		//this is trigger when Eternal Eye is lv3
	public:
		Status_Eternal_Eye_LV3();
		Status* clone() const { return new Status_Eternal_Eye_LV3(*this); };

		int effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event);
	};

	class Status_Lancer_LV2 : public Status_LV
	{
		//this is trigger when Lancer is lv2
	public:
		Status_Lancer_LV2();
		Status* clone() const { return new Status_Lancer_LV2(*this); };

		int effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event);

	private:
		bool m_active = false;

		void generateArmor();
	};

	class Status_Wraith_LV2 : public Status_LV
	{
	public:
		Status_Wraith_LV2();
		Status* clone() const { return new Status_Wraith_LV2(*this); };

		int effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event);
	};

	class Status_Evil_Fiend_LV : public Status_LV
	{
	public:
		Status_Evil_Fiend_LV();
		Status* clone() const { return new Status_Evil_Fiend_LV(*this); };

		int effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event);
	};

	class Status_Gorefiend_LV3 : public Status_LV
	{
	public:
		Status_Gorefiend_LV3();
		Status* clone() const { return new Status_Gorefiend_LV3(*this); };

		int effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event);
	};

	class Status_Slime_LV3 : public Status_LV
	{
		//this is trigger when Archer is lv3
	public:
		Status_Slime_LV3();
		Status* clone() const { return new Status_Slime_LV3(*this); };

		int effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event);
	};
}