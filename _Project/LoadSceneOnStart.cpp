#include "LoadSceneOnStart.h"

LoadSceneOnStart::LoadSceneOnStart(const std::string& p_sceneName) : m_sceneName(p_sceneName)
{

}

LoadSceneOnStart::~LoadSceneOnStart()
{

}

void LoadSceneOnStart::start()
{
	kitten::K_Instance::changeScene(m_sceneName);
}