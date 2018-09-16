#include "AbilityLibrary.h"
#include "TestAbility.h"

//Rock

//This class isn't the database or reader. It only finds and parses data

AbilityLibrary* AbilityLibrary::m_instance = nullptr;

AbilityLibrary::AbilityLibrary()
{
}

AbilityLibrary::~AbilityLibrary()
{
}

AbilityLibrary * AbilityLibrary::getInstance()
{
	return m_instance;
}

AbilityLibrary * AbilityLibrary::getInstanceSafe()
{
	if (m_instance == nullptr)
		m_instance = new AbilityLibrary();
	return m_instance;
}

Ability * AbilityLibrary::findAbility(const std::string &p_name, Unit * p_u)
{
	//TO DO
	//Ability* a = new Ability(p_u);
	if (p_name == "TestAbility")
		return new TestAbility(p_u);
}	

Status * AbilityLibrary::findStatus(const std::string &p_name, Unit * p_u)
{
	//TO DO
	return nullptr;
}
