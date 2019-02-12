#include "UI/DragNDrop.h"
#include "_Project/LerpController.h"

class SpawnUnitOnDrop : public DragNDrop, LerpController::PositionLerpFinishedCallback
{
private:
	void start() override;
	void onClick() override;
	void onDrop() override;
	void onPause() override;
	void onPositionLerpFinished() override;

public:
	SpawnUnitOnDrop();
	~SpawnUnitOnDrop();

	void removeCard();
	void resetCard();
};