#include "IncreaseResolutionOnClick.h"

IncreaseResolutionOnClick::IncreaseResolutionOnClick()
{
	m_enabledOnPause = true;
}

IncreaseResolutionOnClick::~IncreaseResolutionOnClick()
{

}

void IncreaseResolutionOnClick::start()
{
	ClickableUI::start();

	auto parent = getTransform().getParent();
	assert(parent != nullptr);

	m_resController = parent->getAttachedGameObject().getComponent<ResolutionController>();
	assert(m_resController != nullptr);
}

void IncreaseResolutionOnClick::onClick()
{
	m_resController->nextRes();
}