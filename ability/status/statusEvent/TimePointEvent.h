/*@Rock

This is is similar to normal Event.
Its purpose is handle specific time point event for status.

If use normal event system, it will O(n^2)
since it has to trigger all unit and then all status belongs to that unit.

This event system will find the unit who triggers it.
*/

#pragma once
#include "ability/AbilityInfoPackage.h"
#include <unordered_map>
#include <assert.h>

namespace ability
{
	class TimePointEvent
	{
	public:
		enum TPEventType
		{
			Turn_Start = 0,
			Turn_End,
			Level_Up,
			New_Tile,
			Leave_Tile,
			Deal_Damage,
			Receive_Damage,
			Heal,
			Receive_Heal,
		};

		TimePointEvent(TPEventType p_event);
		~TimePointEvent();

		void putInt(const std::string& p_key, int p_value);
		void putPackage(const std::string& p_key, ability::AbilityInfoPackage* p_pack);
		void putGameObject(const std::string& p_key, kitten::K_GameObject* p_value);

		int getInt(const std::string& p_key);
		ability::AbilityInfoPackage* getPackage(const std::string& p_key);
		kitten::K_GameObject* getGameObject(const std::string& p_key);

	private:
		TPEventType m_type; 

		std::unordered_map<std::string, int> *m_intMap;
		std::unordered_map<std::string, kitten::K_GameObject*> *m_gameObjMap;
		std::unordered_map<std::string, ability::AbilityInfoPackage*> *m_packageMap;
	};
}