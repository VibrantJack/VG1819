#pragma once
#include "ability/node/AbilityNode.h"

#include <vector>
#include <assert.h>

//Rock

namespace ability
{
	class AbilityNodeManager
	{
	private:
		static AbilityNodeManager * sm_instance;

		std::unordered_map<NodeName, AbilityNode*> m_nodeList;

		void init();
	public:
		AbilityNodeManager();
		~AbilityNodeManager();

		static void createInstance();
		static void destroyInstance();
		static AbilityNodeManager* getInstance();

		AbilityNode* findNode(NodeName p_name);
	};

}