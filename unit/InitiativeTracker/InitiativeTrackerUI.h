#pragma once
#include "kitten/K_Common.h"
#include "unit/InitiativeTracker/InitiativeTracker.h"
#include "unit/InitiativeTracker/TrackerPointer.h"
#include <vector>

//Rock
//This class handles the UI part of Initiative Tracker
//it contain all UI frame for each unit and modify their transform.

namespace unit
{
	class InitiativeTrackerUI
	{
		friend class TrackerBlock;
	public:
		InitiativeTrackerUI();
		~InitiativeTrackerUI();

		void turnStart();
		void next();
		void change(int p_i);
		int isShown(int p_i);

	private:
		const int m_maxUnitToShow = 5;//there will be maximum number of units to show

		std::vector<TrackerBlock*> m_blockList;

		kitten::K_GameObject* m_initiativeObject;
		kitten::K_GameObject* m_pointerObject;

		const float m_gap = 0.175f;//distance from adjacent frame
		const float m_leftX = -0.25f;//start x coodinate for frame

		std::vector<float> m_xList;//the list of x position for each frame slots
		std::vector<int> m_blockInSlot;//which block in blockInSlot[x]
		std::vector<int> m_unitIndex;//which index of unit the block has
		int m_lastUnitIndex;



		void setPosition();
		void resetPosition();
		void setNewFrame(int p_index);

	};
}