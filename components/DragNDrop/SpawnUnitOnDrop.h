#include "UI/DragNDrop.h"

class SpawnUnitOnDrop : public DragNDrop
{
private:

public:
	SpawnUnitOnDrop():DragNDrop(true){}
	~SpawnUnitOnDrop(){}

	void onHoverStart() override;
	void onHoverEnd() override;
	void onDrop() override;
	void onPause() override;
};