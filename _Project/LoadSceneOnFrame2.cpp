#include "LoadSceneOnFrame2.h"

LoadSceneOnFrame2::LoadSceneOnFrame2(const std::string& p_sceneName) : m_sceneName(p_sceneName)
{

}

LoadSceneOnFrame2::~LoadSceneOnFrame2()
{

}

void LoadSceneOnFrame2::update()
{
	kitten::K_Instance::changeScene(m_sceneName);
}