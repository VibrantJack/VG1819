#pragma once
#include "../DisplayFrame.h"
#include "components/clickables/SetCommanderOnClick.h"
class CommanderDisplayFrame : public DisplayFrame
{
private:
	friend class SetCommanderOnClick;
	const std::vector<int>& m_commanderVector;
	int m_commanderIndex;
public:
	static CommanderDisplayFrame* getActiveInstance();

	void start() override;

	const int& getCurrentPickedCommanderId() const { return m_commanderVector[getCurrentPickedItemIndex()]; } // gives back -1 if no deck has been picked yet
	int getCommanderTiedTo(const kitten::K_GameObject* p_gameObject) { return m_commanderVector[getItemIndexTiedTo(p_gameObject)]; }

	int getTargetAvailable() override;
	void updateIndividualDisplayObject(int p_activeObjectIndex) override;

	void refreshCommander();
	void refreshActiveButtons();
	void onObjectClicked(int p_clickedDataSetIndex);

	CommanderDisplayFrame(int p_marginX, int p_marginY);
	~CommanderDisplayFrame();
};