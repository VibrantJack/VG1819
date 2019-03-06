#include "SavePlayerPrefsOnClick.h"

#include "settings_menu\PlayerPrefs.h"
#include "UniversalSounds.h"

SavePlayerPrefsOnClick::SavePlayerPrefsOnClick()
{

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
		parent->getAttachedGameObject().setEnabled(false);
	}

	UniversalSounds::playSound("click");
}