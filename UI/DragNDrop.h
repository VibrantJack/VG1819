#pragma once
#include "kitten/mouse picking/ClickableUI.h"

class DragNDrop : public kitten::ClickableUI
{
private:
	bool m_isDragging=false, m_backToOrigin= false;
	glm::vec3 m_origin;
public:
	DragNDrop(bool p_backToOrigin = false);
	~DragNDrop();

	virtual void onClick() override;

	virtual void start() override;
	virtual void update() override;

	virtual void onDrop();

	bool hasUpdate() const override { return true; }
};