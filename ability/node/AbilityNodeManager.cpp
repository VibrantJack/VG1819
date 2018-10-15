#include "AbilityNodeManager.h"


//Rock

namespace ability
{
	AbilityNodeManager* AbilityNodeManager::sm_instance = nullptr;

	void AbilityNodeManager::init()
	{
		AbilityNode* newNode;

		//TO DO: improve
		newNode = new ChangeAttributeNode();
		newNode->m_name = "ChangeAttributeNode";
		m_nodeList.push_back(newNode);

		newNode = new CheckHPNode();
		newNode->m_name = "CheckHPNode";
		m_nodeList.push_back(newNode);

		newNode = new ChangeAbilityDescriptionNode();
		newNode->m_name = "ChangeAbilityDescriptionNode";
		m_nodeList.push_back(newNode);

		newNode = new ChangeAbilityInfoNode();
		newNode->m_name = "ChangeAbilityInfoNode";
		m_nodeList.push_back(newNode);

		newNode = new SpawnUnitNode();
		newNode->m_name = "SpawnUnitNode";
		m_nodeList.push_back(newNode);
	}

	AbilityNodeManager::AbilityNodeManager()
	{
		init();
	}

	AbilityNodeManager::~AbilityNodeManager()
	{
		auto end = m_nodeList.end();
		for (auto it = m_nodeList.begin(); it != end; ++it)
		{
			delete (*it);
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

	AbilityNode* AbilityNodeManager::findNode(const std::string & p_name)
	{
		for (auto it = m_nodeList.begin(); it != m_nodeList.end(); it++)
		{
			if ((*it)->m_name == p_name)
				return *it;
		}
		return nullptr;
	}

}