#pragma once
#include "AbilityNode.h"

#include <vector>
#include <assert.h>

//Rock

namespace ability
{
	class AbilityNodeManager
	{
	private:
		static AbilityNodeManager * sm_instance;

		std::vector<AbilityNode*> m_nodeList;

		void init();
	public:
		AbilityNodeManager();
		~AbilityNodeManager();

		static void createInstance();
		static void destroyInstance();
		static AbilityNodeManager* getInstance();

		AbilityNode* findNode(const std::string& p_name);
	};

}