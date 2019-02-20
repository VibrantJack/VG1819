#pragma once
#include "StatusManager.h"
//#include "ability/status/Status_Block.cpp"
//Rock

namespace ability
{
	StatusManager* StatusManager::sm_instance = nullptr;

	void StatusManager::init()
	{
		Status* s;

		s = new Status_Encourage();
		m_statusList[STATUS_ENCOURAGE] = s;

		s = new Status_LV();
		m_statusList[STATUS_LV] = s;

		s = new Status_Priest_LV3();
		m_statusList[STATUS_PRIEST_LV3] = s;

		s = new Status_Archer_LV3();
		m_statusList[STATUS_ARCHER_LV3] = s;

		s = new Status_Duelist_LV3();
		m_statusList[STATUS_DUELIST_LV3] = s;

		s = new Status_Dodge();
		m_statusList[STATUS_DODGE] = s;

		s = new Status_Temp_Change();
		m_statusList[STATUS_TEMP_CHANGE] = s;

		s = new Status_AD_Change();
		m_statusList[STATUS_AD_CHANGE] = s;

		s = new Status_Load();
		m_statusList[STATUS_LOAD] = s;

		s = new Status_Shield();
		m_statusList[STATUS_SHIELD] = s;

		s = new Status_Block();
		m_statusList[STATUS_BLOCK] = s;

		s = new Status_Curse();
		m_statusList[STATUS_CURSE] = s;

		s = new Status_Eternal_Eye_LV3();
		m_statusList[STATUS_ETERNAL_EYE_LV3] = s;

		s = new Status_DR_Eternal_Eye();
		m_statusList[STATUS_DR_ETERNAL_EYE] = s;

		s = new Status_Lancer_LV2();
		m_statusList[STATUS_LANCER_LV2] = s;

		s = new Status_DR_Mud_Demon();
		m_statusList[STATUS_DR_MUD_DEMON] = s;

		ADD_ELEMENT(s, m_statusList, STATUS_IN_CHANGE, Status_IN_Change);
		ADD_ELEMENT(s, m_statusList, STATUS_DR_HORROR_LORD, Status_DR_Horror_Lord);
		ADD_ELEMENT(s, m_statusList, STATUS_ATTACH, Status_Attach);
		ADD_ELEMENT(s, m_statusList, STATUS_WRAITH_LV2, Status_Wraith_LV2);
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
			delete it->second;
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
		return m_statusList[p_name]->clone();
	}

}
