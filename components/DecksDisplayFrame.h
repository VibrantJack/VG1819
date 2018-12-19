#pragma once
#include "UI/UIFrame.h"
#include "kitten/K_GameObject.h"
#include <vector>

class DecksDisplayFrame : public kitten::K_Component
{
private:
	std::vector<kitten::K_GameObject*> m_slots, m_slotTexts;
	kitten::K_GameObject* m_arrows[2], *m_highlight;
	int m_margin = 10, // the space between elements within this frame
		m_currentSet = 0,  // the current set of decks being displayed
		m_currentActive = 0, // the number of decks currently need to be displayed
		m_currentPick = -1; // the current picked deck
	static bool sm_survivorFlagged;

	void updateDeckDisplay();
	void updateHighlight();

	virtual void onDisabled();
	virtual void onEnabled();
public:
	static DecksDisplayFrame* getActiveInstance();

	void start() override;

	void offsetCurrentSet(const int p_offset);
	const int& getCurrentPickedDeckId() const; // gives back -1 if no deck has been picked yet
	void pickDisplayedDeck(const kitten::K_GameObject* p_gameObject);

	DecksDisplayFrame(const int p_margin);
	~DecksDisplayFrame();
};