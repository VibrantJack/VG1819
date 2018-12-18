#include "UI/DragNDrop.h"

class SpawnUnitOnDrop : public DragNDrop
{
private:

public:
	SpawnUnitOnDrop():DragNDrop(true){}
	~SpawnUnitOnDrop(){}

	void onDrop() override;
};