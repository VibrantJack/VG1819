#include "ShowLoadingOnClick.h"

#include "kitten\K_GameObjectManager.h"

ShowLoadingOnClick::ShowLoadingOnClick() : m_loadingScreen(nullptr)
{

}

ShowLoadingOnClick::~ShowLoadingOnClick()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::Remove_Loading_Screen, this);
}

void ShowLoadingOnClick::start()
{
	ClickableUI::start();

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::Remove_Loading_Screen,
		this,
		std::bind(&ShowLoadingOnClick::disableLoadingScreen, this, std::placeholders::_1, std::placeholders::_2)
	);

	if (m_loadingScreen != nullptr)
	{
		int i = 0;
	}

	m_loadingScreen = kitten::K_GameObjectManager::getInstance()->createNewGameObject(LOADING_SCREEN_JSON);
	assert(m_loadingScreen != nullptr);

	m_loadingScreen->setEnabled(false);
}

void ShowLoadingOnClick::onClick()
{
	m_loadingScreen->setEnabled(true);
}

void ShowLoadingOnClick::disableLoadingScreen(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	m_loadingScreen->setEnabled(false);
}