#pragma once
#include "DisplayFrame.h"
class DecksDisplayFrame : public DisplayFrame
{
private:

public:
	static DecksDisplayFrame* getActiveInstance();

	void start() override;

	void offsetCurrentSet(const int p_offset) { DisplayFrame::offsetCurrentSet(p_offset); }
	const int& getCurrentPickedDeckId() const { return getCurrentPickedObject(); } // gives back -1 if no deck has been picked yet
	
	void onObjectClicked(int p_deckId) override;
	int getTargetAvailable() override;
	void updateIndividualDisplayObject(int p_activeObjectIndex) override;

	DecksDisplayFrame(int p_marginX, int p_marginY);
	~DecksDisplayFrame();
};