#pragma once
#include "kitten/K_Common.h"
#include "unit/InitiativeTracker/InitiativeTracker.h"
#include <vector>

//Rock
//This class handles the UI part of Initiative Tracker
//it contain all UI frame for each unit and modify their transform.

namespace unit
{
	class InitiativeTrackerUI : public kitten::K_Component
	{
	public:
		InitiativeTrackerUI();
		~InitiativeTrackerUI();

		void turnStart();
		void next();
		void remove(const kitten::K_GameObject* p_unit);
		int isShown(const kitten::K_GameObject* p_unit);

	private:
		const float m_scaleX = 0.15f;
		const float m_scaleY = 0.2f;
		const float m_gap = 0.175f;
		const float m_frameY = 0.8f;
		const float m_textY = 0.6f;
		const float m_leftX = -0.25f;
		const int m_maxUnitToShow = 5;//there will be maximum number of units to show

		std::vector<kitten::K_GameObject*> m_frameList;//the list of frames
		std::vector<kitten::K_GameObject*> m_textList;//the list of textbox
		std::vector<kitten::K_GameObject*>::iterator m_lastShownUnitIterator;
		std::vector<kitten::K_GameObject*>::iterator m_firstShownUnitIterator;

		std::vector<float> m_xList;//the list of x position for each frame slots
		std::vector<int> m_frameIndexList;
		//m_frameIndexList[a] = b means m_frameList[a] is in y slots, its x position should be m_xList[b];

		const std::string m_blankTexture = "textures/ui/blankFrame.tga";

		void setPosition();
		void moveX(int p_xI, int p_fI);
		void resetPosition();
		void resetScale();
		void setUIFrame(std::vector<kitten::K_GameObject*>::iterator p_unitIt, int p_index);
		void setNewFrame(int p_index);

		void setArrow();



	};
}