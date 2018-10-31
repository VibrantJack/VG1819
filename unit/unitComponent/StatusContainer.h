#pragma once
#include "ability/status/Status.h"
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

	public:
		std::vector<ability::Status*> m_statusList;
		Unit* m_unit;

		StatusContainer();
		~StatusContainer();

		void addStatus(ability::Status *p_newStatus);
		bool removeStatus(const ability::Status *p_oldStatus);
		ability::Status* getStatus(const std::string& p_name);

		void registerTP(ability::TimePointEvent::TPEventType p_type, ability::Status* p_status);
		void deregisterTP(ability::TimePointEvent::TPEventType p_type, ability::Status* p_status);
		void triggerTP(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent* p_event);

	};
}
