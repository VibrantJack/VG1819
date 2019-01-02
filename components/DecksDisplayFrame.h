#pragma once
#include "DisplayFrame.h"
#include "components/clickables/AddNewDeckOnClick.h"
#include "components/clickables/DeleteDeckOnClick.h"
class DecksDisplayFrame : public DisplayFrame
{
private:
	friend class DeleteDeckOnClick;
	friend class AddNewDeckOnClick;
public:
	static DecksDisplayFrame* getActiveInstance();

	void start() override;

	const int& getCurrentPickedDeckId() const { return getCurrentPickedItemIndex(); } // gives back -1 if no deck has been picked yet
	
	void onObjectClicked(int p_deckId) override;
	int getTargetAvailable() override;
	void updateIndividualDisplayObject(int p_activeObjectIndex) override;

	DecksDisplayFrame(int p_marginX, int p_marginY);
	~DecksDisplayFrame();
};