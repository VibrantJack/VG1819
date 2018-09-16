#pragma once
#include "Ability.h"
#include "Status.h"

class AbilityLibrary
{
private:
	static AbilityLibrary * m_instance;
public:
	AbilityLibrary();
	~AbilityLibrary();

	static AbilityLibrary* getInstance();
	static AbilityLibrary* getInstanceSafe();

	Ability* findAbility(const std::string &p_name, Unit* p_u);
	Status* findStatus(const std::string &p_name, Unit* p_u);
};
