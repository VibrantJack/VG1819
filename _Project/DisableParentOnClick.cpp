#include "DisableParentOnClick.h"

DisableParentOnClick::DisableParentOnClick()
{

}

DisableParentOnClick::~DisableParentOnClick()
{

}

void DisableParentOnClick::onClick()
{
	kitten::Transform* parent = getTransform().getParent();

	if (parent != nullptr)
	{
		parent->getAttachedGameObject().setEnabled(false);
	}
}