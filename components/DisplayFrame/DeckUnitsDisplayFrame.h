#pragma once
#include "../DisplayFrame.h"
#include "DeckData.hpp"
class DeckUnitsDisplayFrame : public DisplayFrame
{
private:
	DeckData* m_deckData;
public:
	static DeckUnitsDisplayFrame* getActiveInstance();

	void start() override;

	void offsetCurrentSet(const int p_offset) { DisplayFrame::offsetCurrentSet(p_offset); }
	const int& getCurrentPickedUnitId() const { return getCurrentPickedObject(); } // gives back -1 if no deck has been picked yet



	int getTargetAvailable();
	void updateIndividualDisplayObject(int p_activeObjectIndex);

	DeckUnitsDisplayFrame(int p_marginX, int p_marginY);
	~DeckUnitsDisplayFrame();
};