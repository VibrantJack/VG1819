#pragma once
#include "ability/status/Status.h"
#include "ability/status/demonic_restriction/Status_Demonic_Restriction.h"
#include <string>
#include <vector>

//Rock

//This class will contain a list of status

namespace unit
{
	class StatusContainer
	{
	private:
		std::unordered_map<ability::TimePointEvent::TPEventType, std::vector<ability::Status*>*>* m_TPStatusList;
		std::vector<ability::Status*> m_removeQueue;
		Unit* m_unit;
	public:
		std::vector<ability::Status*> m_statusList;

		StatusContainer(Unit* p_unit);
		~StatusContainer();

		void addStatus(ability::Status *p_newStatus);
		void queueRemove(ability::Status *p_oldStatus);
		bool removeStatus(const ability::Status *p_oldStatus);
		ability::Status* getStatus(const std::string& p_Id, const std::string& p_source = "ANY");

		void registerTP(ability::TimePointEvent::TPEventType p_type, ability::Status* p_status);
		void deregisterTP(ability::TimePointEvent::TPEventType p_type, ability::Status* p_status);
		void triggerTP(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent* p_event);

		Unit* getUnit();

	private:
		void addToStatusList(ability::TimePointEvent::TPEventType p_type, ability::Status* p_status);
	};
}
