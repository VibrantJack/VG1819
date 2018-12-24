#include "UI/DragNDrop.h"
#include "_Project/LerpController.h"

class SpawnUnitOnDrop : public DragNDrop, public kitten::TransformPositionListener
{
private:
	bool m_isHovered = false; 
public:
	SpawnUnitOnDrop():DragNDrop(true){}
	~SpawnUnitOnDrop();

	void start() override;
	void onHoverStart() override;
	void onHoverEnd() override;
	void onDrop() override;
	void onPause() override;
	void onPosChanged(const glm::vec3& p_newPos) override;
};