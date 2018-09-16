#include <iostream>
#include "DebugPrintOnce.h"
#include "kitten\K_ComponentManager.h"

DebugPrintOnce::DebugPrintOnce(const std::string p_message) : m_message(p_message)
{

}

DebugPrintOnce::~DebugPrintOnce()
{
	std::cout << "DebugPrintOnce deleted" << std::endl;
}

void DebugPrintOnce::update()
{
	std::cout << "[Debug] " << m_message << std::endl;
	kitten::K_ComponentManager::getInstance()->destroyComponent(this);
}