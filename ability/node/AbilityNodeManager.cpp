#include "AbilityNodeManager.h"
#include "ChangeCounterNode.h"
#include "ChangeHPNode.h"

AbilityNodeManager* AbilityNodeManager::sm_instance = nullptr;

void AbilityNodeManager::init()
{
	AbilityNode* newNode;

	newNode = new ChangeCounterNode();
	newNode->m_name = "ChangeCounterNode";
	m_nodeList.push_back(newNode);

	newNode = new ChangeHPNode();
	newNode->m_name = "ChangeHPNode";
	m_nodeList.push_back(newNode);
}

AbilityNodeManager::AbilityNodeManager()
{
	init();
}

AbilityNodeManager::~AbilityNodeManager()
{
	m_nodeList.clear();
}

void AbilityNodeManager::createInstance()
{
	assert(sm_instance == nullptr);
	sm_instance = new AbilityNodeManager();
}

void AbilityNodeManager::destroyInstance()
{
	assert(sm_instance != nullptr);
	delete sm_instance;
	sm_instance = nullptr;
}

AbilityNodeManager * AbilityNodeManager::getInstance()
{
	assert(sm_instance != nullptr);
	return sm_instance;
}

AbilityNode* AbilityNodeManager::findNode(const std::string & p_name)
{
	for (auto it = m_nodeList.begin(); it != m_nodeList.end(); it++)
	{
		if ((*it)->m_name == p_name)
			return *it;
	}
	return nullptr;
}
