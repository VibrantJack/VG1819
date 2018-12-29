#pragma once
#include "../DisplayFrame.h"
class CommanderDisplayFrame : public DisplayFrame
{
private:
	const std::vector<int>& m_commanderVector;
public:
	static CommanderDisplayFrame* getActiveInstance();

	void start() override;

	void offsetCurrentSet(const int p_offset) { DisplayFrame::offsetCurrentSet(p_offset); }
	const int& getCurrentPickedCommanderId() const { return getCurrentPickedObject(); } // gives back -1 if no deck has been picked yet



	int getTargetAvailable();
	void updateIndividualDisplayObject(int p_activeObjectIndex);

	CommanderDisplayFrame(int p_marginX, int p_marginY);
	~CommanderDisplayFrame();
};