#pragma once
#include "kitten/mouse picking/ClickableUI.h"
#include "_Project/LerpController.h"
#include "UI\CardContext.h"
#include "unit/Unit.h"

class HoverOverCardBehavior : public kitten::ClickableUI
{
protected:
	bool m_isHovered = false;
	glm::vec3 m_origin = {};
	CardContext* m_cardContext;
	unit::Unit* m_unit;
	
	LerpController* m_lerpController = nullptr;
public:
	HoverOverCardBehavior();
	~HoverOverCardBehavior();

	bool isHovered() { return m_isHovered; }
	glm::vec3& getOrigin() { return m_origin; }

	void start() override;

	void onHoverStart() override;
	void onHoverEnd() override;

	void setCardContext(CardContext* p_context) { m_cardContext = p_context; }
};
