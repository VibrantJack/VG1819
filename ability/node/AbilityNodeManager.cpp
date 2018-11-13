#include "AbilityNodeManager.h"


//Rock

namespace ability
{
	AbilityNodeManager* AbilityNodeManager::sm_instance = nullptr;

	void AbilityNodeManager::init()
	{
		AbilityNode* newNode;

		newNode = new ChangeAttributeNode();
		m_nodeList[ability::ChangeAttribute] = newNode;

		newNode = new CheckHPNode();
		m_nodeList[ability::CheckHP] = newNode;

		newNode = new ChangeAbilityDescriptionNode();
		m_nodeList[ability::ChangeAbilityDescription] = newNode;

		newNode = new ChangeAbilityInfoNode();
		m_nodeList[ability::ChangeAbilityInfo] = newNode;

		newNode = new SpawnUnitNode();
		m_nodeList[ability::SpawnUnit] = newNode;
	}

	AbilityNodeManager::AbilityNodeManager()
	{
		init();
	}

	AbilityNodeManager::~AbilityNodeManager()
	{
		for (auto it = m_nodeList.begin(); it != m_nodeList.end(); ++it)
		{
			delete it->second;
		}
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

	AbilityNode* AbilityNodeManager::findNode(NodeName p_name)
	{
		return m_nodeList[p_name];
	}

}