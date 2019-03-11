#include "DecreaseResolutionOnClick.h"

DecreaseResolutionOnClick::DecreaseResolutionOnClick() : m_resController(nullptr)
{
	m_enabledOnPause = true;
}

DecreaseResolutionOnClick::~DecreaseResolutionOnClick()
{

}

void DecreaseResolutionOnClick::start()
{
	ClickableUI::start();

	auto parent = getTransform().getParent();
	assert(parent != nullptr);

	m_resController = parent->getAttachedGameObject().getComponent<ResolutionController>();
	assert(m_resController != nullptr);
}

void DecreaseResolutionOnClick::onClick()
{
	m_resController->prevRes();
}