#pragma once
#include "UnitCommon.h"


//Rock

class Unit
{
public:
	std::string m_ID;

	std::vector<std::string> m_tags;
	std::string m_name;

	std::map<std::string, int> m_attributes;
	//attributes includes all numerical attribute and counter

	/*
	int m_maxHP;
	int m_HP;
	int m_baseMV;
	int m_MV;
	int m_baseIN;
	int m_IN;
	int m_baseCost;
	int m_Cost;
	int m_LV;

	std::map<std::string, int> m_Counter;
	*/

	UnitSize m_size;

	std::vector<std::string> m_Ability;//TO DO: should include more information such as power, counter

	std::vector<Status*> m_Status;

	Unit();
	~Unit();

	void addStatus(Status *p_newStatus);
	bool removeStatus(Status *p_oldStatus);

	std::vector<Status*> getStatus() { return m_Status; };

	int useAbility(int p_abilityIndex);//TO DO

	int callStatus(int p_StatusIndex, int p_event);
	//event is the one of the events that this status registered
	//should be enum, I didn't define it yet, so use int as place holder
};

