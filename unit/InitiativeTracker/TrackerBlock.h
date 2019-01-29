#pragma once
#include "kitten/K_Common.h"
#include "unit/InitiativeTracker/InitiativeTrackerUI.h"
#include "UI/CardContext.h"
#include <vector>

//Rock
//This class handles the UI of each block in Initiative Tracker
//It contains a UI frame for unit
//A textbox for display information of unit
//A clickable for interative
//It also contains the movement of slot

namespace unit
{
	class TrackerBlock : public kitten::K_Component
	{
	public:
		const static float sm_halfWinX;
		const static float sm_halfWinY;

		TrackerBlock();
		~TrackerBlock();
		
		void setTrackerUI(InitiativeTrackerUI* p_UI);
		void start() override;

		void move(int p_slotIndex);
		void set(kitten::K_GameObject* p_unitGO);
		void clear();

		bool hasUpdate() const override;
		void update() override;

		//void registerEvent();
		//void deregisterEvent();
		//void listenEvent();
	private:
		InitiativeTrackerUI* m_trackerUI;

		kitten::K_GameObject* m_frameObject;//the object contains frame and clickable
		//kitten::K_GameObject* m_textObject; no longer needed. The object contains textbox and background
		

		int m_currentSlotIndex;//block is currently in this slot
		int m_targetSlotIndex;//block is moving to this slot
		float distance;//distance between current x position to target slot's x position

		//void showTextbox();
		//void hideTextbox();

		//static varibles
		const static std::string sm_blankTexture;
		const static std::string sm_blankText;

		const static int sm_offsetY;
		float m_frameY;//y coodinate for frame

		//const static int sm_startX;

		const static float sm_textY;

		const static float sm_speed;

		const static int sm_margin;
	};
}
