#pragma once
#include "kitten/K_GameObject.h"
#include "kitten/K_Component.h"
#include <vector>
#include <string>

class DisplayFrame : public kitten::K_Component
{
protected:
	std::vector<kitten::K_GameObject*> m_objectsToDisplay;
	kitten::K_GameObject* m_arrows[2], *m_highlight, *m_empty;
	const std::string m_displayObject, m_arrowFileLeft, m_arrowFileRight, m_highlightFile, m_emptyFile;

	int m_marginX = 10, // the space between elements within this frame
		m_marginY = 5,
		m_highlightOffset = 5, // the offset for highlights 
		m_currentSet = 0,  // the current set of decks being displayed
		m_currentActive = 0, // the number of decks currently need to be displayed
		m_currentPick = -1; // the current picked deck

	void updateDisplay();
	void updateHighlight();

	virtual void onDisabled();
	virtual void onEnabled();

	virtual int getTargetAvailable() { return 0; } // override to give it the total count of objects it has to deal with (i.e. decks, units, etc)
	virtual void updateIndividualDisplayObject(int p_activeObjectIndex) {} // override to add customized changes to the children in an object. 
	// The order the objects come in help in determining how they get loaded

public:
	void start() override;

	void offsetCurrentSet(const int p_offset);
	const int& getCurrentPickedObject() const; // gives back -1 if no object highlight has been picked yet
	int pickDisplayedObject(const kitten::K_GameObject* p_gameObject);

	DisplayFrame(int p_marginX, int p_marginY, const std::string& p_displayObject, const std::string& p_arrowLeft, std::string& p_arrowRight, const std::string& p_highlight, const std::string p_empty)
		: m_marginX(p_marginX), m_marginY(p_marginY), m_displayObject(p_displayObject), m_arrowFileLeft(p_arrowLeft), m_arrowFileRight(p_arrowRight), m_highlightFile(p_highlight), m_emptyFile(p_empty)
	{}
	~DisplayFrame(){}
};