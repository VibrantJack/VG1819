#include "SceneSwitchComponent.hpp"
#include "kibble/kibble.hpp"
#include "kitten/K_Instance.h"

void SceneSwitchComponent::onClick(){
	kitten::K_Instance::flagSceneChange(m_targetScene);
	//kitten::K_GameObjectManager::getInstance()->destroyAllGameObjects();
	//kibble::setSceneFrom(m_targetScene);
}

SceneSwitchComponent::SceneSwitchComponent(std::string p_sceneTarget) : m_targetScene(p_sceneTarget) {}
SceneSwitchComponent::~SceneSwitchComponent() {
}