#pragma once
#include "../DisplayFrame.h"
#include "components/clickables/ChangeUnitOnClick.h"
#include "components/clickables/AddUnitOnClick.h"
#include "DeckData.hpp"
class DeckUnitsDisplayFrame : public DisplayFrame
{
private:
	friend class ChangeUnitOnClick;
	friend class AddUnitOnClick;
	DeckData* m_deckData;
public:
	static DeckUnitsDisplayFrame* getActiveInstance();

	void start() override;

	int getTargetAvailable();
	void updateIndividualDisplayObject(int p_activeObjectIndex);

	DeckUnitsDisplayFrame(int p_marginX, int p_marginY);
	~DeckUnitsDisplayFrame();
};