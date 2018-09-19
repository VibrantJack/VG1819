#pragma once
#include "ability/node/AbilityNode.h"

#include <string>
#include <map>
#include <vector>

//Rock

//Status include Buff, Debuff, Passive Ability, and level up bonus
//It has ability nodes as Ability, but the effects are triggered by some event or time point

//Event can be a enum, such as Level up, Turn Start, Tile Change....
//Status should register some of the event to something high level
//when any of the event occurs, high level class should notify this
//and this should do something based on which event occur.

//EXAMPLE: Demonic Restriction will handle Tile Change event
//if it's not Demonic Presence Tile, its effect will activate
//otherwise deactivate

//EXAMPLE: a "Until next turn" Status will handle Turn Start event
//it will decrease duration by 1 and see if it's zero
//then decide to remove this effect


namespace ability
{
	enum TimePointEvent
	{
		Turn_Start,
		Turn_End,
		Level_Up,
		New_Tile,
		Deal_Damage,
		Receive_Damage,
	};

	class Status
	{
	public:
		unit::Unit * m_unit;//the unit this status attached to

		std::map<std::string, int> m_counter;
		//Most commonly counter is duration. But it can be more, such as how many times it can be used

		std::string m_name;
		std::string m_description;//the text that will be showed to player
		std::vector<AbilityNode*> m_abilityNodes;//the list of nodes that will affect

												 //TO DO: Register Event

		virtual int effectDefault() = 0;//this is effect that activates when status is added
		virtual int effectOnTimePoint(TimePointEvent* p_timePoint) = 0;
		//TO DO: Listen Event and take effect
		//Maybe use Chain of Responsibility

		Status(unit::Unit * p_unit) { m_unit = p_unit; };
		~Status();

	private:
		int removeThis();//TO DO: remove this Status from Unit, and delete the instance
	};
}



