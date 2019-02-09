#include "UI/DragNDrop.h"
#include "_Project/LerpController.h"

class SpawnUnitOnDrop : public DragNDrop, LerpController::PositionLerpFinishedCallback
{
public:
	SpawnUnitOnDrop();
	~SpawnUnitOnDrop();

	void start() override;
	void onClick() override;
	void onDrop() override;
	void onPause() override;
	void onPositionLerpFinished() override;

	void removeCard();
	void resetCard();
};