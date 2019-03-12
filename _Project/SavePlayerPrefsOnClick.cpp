#include "SavePlayerPrefsOnClick.h"

#include "settings_menu\PlayerPrefs.h"
#include "UniversalSounds.h"

SavePlayerPrefsOnClick::SavePlayerPrefsOnClick()
{
	m_enabledOnPause = true;
}

SavePlayerPrefsOnClick::~SavePlayerPrefsOnClick()
{

}

void SavePlayerPrefsOnClick::onClick()
{
	PlayerPrefs::saveAllSettings();

	kitten::Transform* parent = getTransform().getParent();

	if (parent != nullptr)
	{
		kitten::Transform* parentParent = parent->getParent();

		if (parentParent != nullptr)
		{
			parentParent->getAttachedGameObject().setEnabled(false);
		}
	}

	UniversalSounds::playSound("click");
}