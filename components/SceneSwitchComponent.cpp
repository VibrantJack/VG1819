#include "SceneSwitchComponent.hpp"
#include "kibble/kibble.hpp"
#include "kitten/K_Instance.h"

void SceneSwitchComponent::onClick(){
	onPreSwitch();
	kitten::K_Instance::flagSceneChange(m_targetScene);
}

SceneSwitchComponent::SceneSwitchComponent(std::string p_sceneTarget) : m_targetScene(p_sceneTarget) {}
SceneSwitchComponent::~SceneSwitchComponent() {
}

#include <iostream>
void SceneSwitchComponent::onPreSwitch() {
	std::cout << "Scene is Switching! >";
}