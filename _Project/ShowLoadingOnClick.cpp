#include "ShowLoadingOnClick.h"

#include "kitten\K_GameObjectManager.h"

ShowLoadingOnClick::ShowLoadingOnClick() : m_loadingScreen(nullptr)
{

}

ShowLoadingOnClick::~ShowLoadingOnClick()
{

}

void ShowLoadingOnClick::start()
{
	ClickableUI::start();

	m_loadingScreen = kitten::K_GameObjectManager::getInstance()->createNewGameObject(LOADING_SCREEN_JSON);
	assert(m_loadingScreen != nullptr);

	m_loadingScreen->setEnabled(false);
}

void ShowLoadingOnClick::onClick()
{
	m_loadingScreen->setEnabled(true);
}