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
	int pickDisplayedDeck(const kitten::K_GameObject* p_gameObject) { return pickDisplayedObject(p_gameObject); }

	int getTargetAvailable();
	void updateIndividualDisplayObject(int p_activeObjectIndex);

	DecksDisplayFrame(int p_marginX, int p_marginY);
	~DecksDisplayFrame();
};