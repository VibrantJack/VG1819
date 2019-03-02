#include "SavePlayerPrefsOnClick.h"

#include "settings_menu\PlayerPrefs.h"

SavePlayerPrefsOnClick::SavePlayerPrefsOnClick()
{

}

SavePlayerPrefsOnClick::~SavePlayerPrefsOnClick()
{

}

void SavePlayerPrefsOnClick::onClick()
{
	PlayerPrefs::saveAllSettings();
}