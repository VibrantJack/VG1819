#pragma once
#include "../DisplayFrame.h"
class UnitDisplayFrame : public DisplayFrame
{
private:
	const std::vector<int>& m_unitVector;
public:
	static UnitDisplayFrame* getActiveInstance();

	void start() override;

	void offsetCurrentSet(const int p_offset) { DisplayFrame::offsetCurrentSet(p_offset); }
	const int& getCurrentPickedUnitId() const { return getCurrentPickedObject(); } // gives back -1 if no deck has been picked yet



	int getTargetAvailable();
	void updateIndividualDisplayObject(int p_activeObjectIndex);

	UnitDisplayFrame(int p_marginX, int p_marginY);
	~UnitDisplayFrame();
};