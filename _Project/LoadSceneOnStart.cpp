#include "LoadSceneOnStart.h"

LoadSceneOnStart::LoadSceneOnStart(nlohmann::json & p_json) : kitten::K_Component(p_json),
	m_sceneName(LOOKUPSTR("scene_name"))
{
}

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