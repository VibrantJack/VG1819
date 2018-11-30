#pragma once
#include "UI/UIFrame.h"
#include "kitten/K_GameObject.h"
#include <vector>

class DecksDisplayFrame : public kitten::K_Component
{
private:
	std::vector<kitten::K_GameObject*> m_slots, m_slotTexts;
	kitten::K_GameObject* m_arrows[2];
	int m_margin = 10, // the space between elements within this frame
		m_currentSet = 0,  // the current set of decks being displayed
		m_currentActive = 0,
		m_currentPick;

	void updateDeckDisplay();

	virtual void onDisabled();
	virtual void onEnabled();
public:
	static DecksDisplayFrame* getActiveInstance();

	void start() override;

	void offsetCurrentSet(const int& p_offset);

	DecksDisplayFrame( const int& p_margin);
	~DecksDisplayFrame();
};