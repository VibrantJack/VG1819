#pragma once

#include "ActionSelect.h"




namespace unit
{
	class ActionMap
	{
	public:
		ActionMap();
		~ActionMap();

		void act(ActionSelect* p_s);

	protected:
		std::unordered_map<std::string, void(ActionMap::*)(ActionSelect* p_s)> m_funcMap;

		void end(ActionSelect* p_s);
		void move(ActionSelect* p_s);
		void join(ActionSelect* p_s);
		void action(ActionSelect* p_s);
		void useAbility(ActionSelect* p_s);
		void lvUp(ActionSelect* p_s);
		void destory(ActionSelect* p_s);
		void setDP(ActionSelect* p_s);
	};
}
