#include "StatusManager.h"

//Rock

namespace ability
{
	StatusManager* StatusManager::sm_instance = nullptr;

	void StatusManager::init()
	{
		Status* s;

		//TO DO: need improve
		s = new Status_CD();
		s->m_name = "Status_CD";
		m_statusList.push_back(s);

		s = new Status_Encourage();
		s->m_name = "Status_Encourage";
		m_statusList.push_back(s);

		s = new Status_LV();
		s->m_name = "Status_LV";
		m_statusList.push_back(s);

		s = new Status_Priest_LV3();
		s->m_name = "Status_Priest_LV3";
		m_statusList.push_back(s);

		s = new Status_Archer_LV3();
		s->m_name = "Status_Archer_LV3";
		m_statusList.push_back(s);

		s = new Status_Duelist_LV3();
		s->m_name = "Status_Duelist_LV3";
		m_statusList.push_back(s);

		s = new Status_Dodge();
		s->m_name = "Status_Dodge";
		m_statusList.push_back(s);
	}

	StatusManager::StatusManager()
	{
		init();
	}

	StatusManager::~StatusManager()
	{
		auto end = m_statusList.end(); 
		for (auto it = m_statusList.begin(); it != end; ++it)
		{
			delete (*it);
		}
	}

	void StatusManager::createInstance()
	{
		assert(sm_instance == nullptr);
		sm_instance = new StatusManager();
	}

	void StatusManager::destroyInstance()
	{
		assert(sm_instance != nullptr);
		delete sm_instance;
		sm_instance = nullptr;
	}

	StatusManager * StatusManager::getInstance()
	{
		assert(sm_instance != nullptr);
		return sm_instance;
	}

	Status * StatusManager::findStatus(const std::string & p_name)
	{
		for (auto it = m_statusList.begin(); it != m_statusList.end(); it++)
		{
			if ((*it)->m_name == p_name)
			{
				//return a copy of the status
				return (*it)->clone();
			}
		}
		return nullptr;
	}

}
