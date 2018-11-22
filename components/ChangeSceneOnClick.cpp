#include "ChangeSceneOnClick.hpp"
#include "kibble/kibble.hpp"
#include "kitten/K_Instance.h"

void ChangeSceneOnClick::onClick(){
	onPreSwitch();
	kitten::K_Instance::changeScene(m_targetScene);
}

ChangeSceneOnClick::ChangeSceneOnClick(const std::string& p_sceneTarget) : m_targetScene(p_sceneTarget) {}
ChangeSceneOnClick::~ChangeSceneOnClick() {
}

#include <iostream>
void ChangeSceneOnClick::onPreSwitch() {
	std::cout << "Scene is Switching! >";
}