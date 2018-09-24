#include "ComponentDataType.hpp"

#include "_Project/MoveByMouseRightClickDrag.h"
kitten::K_Component* getMoveByMouseRightClickDragComponentDataFrom(nlohmann::json* p_jsonfile) {
	float speed = 0.005f;

	if (p_jsonfile->find("speed") != p_jsonfile->end()) {
		speed = p_jsonfile->operator[]("speed");
	}

	return new MoveByMouseRightClickDrag(speed);
}

#include "_Project/ZoomByMouseWheel.h"
kitten::K_Component* getZoomByMouseWheelComponentDataFrom(nlohmann::json* p_jsonfile) {
	float speed = 1.0f;
	int minFOV = 1, maxFOV = 90;

	if (p_jsonfile->find("speed") != p_jsonfile->end()) {
		speed = p_jsonfile->operator[]("speed");
	}

	if (p_jsonfile->find("minfov") != p_jsonfile->end()) {
		minFOV = p_jsonfile->operator[]("minfov");
	}

	if (p_jsonfile->find("maxfov") != p_jsonfile->end()) {
		maxFOV = p_jsonfile->operator[]("maxfov");
	}

	return new ZoomByMouseWheel(speed, minFOV, maxFOV); // TODO attributes
}

#include "kitten/Camera.h"
kitten::K_Component* getCameraComponentDataFrom(nlohmann::json* p_jsonfile) {
	kitten::Camera* component = new kitten::Camera();
	if (p_jsonfile->find("fov") != p_jsonfile->end()) {
		component->setFOV(p_jsonfile->operator[]("fov"));
	}

	if (p_jsonfile->find("near") != p_jsonfile->end()) {
		component->setNearClip(p_jsonfile->operator[]("near"));
	}

	if (p_jsonfile->find("far") != p_jsonfile->end()) {
		component->setFarClip(p_jsonfile->operator[]("far"));
	}

	if (p_jsonfile->find("width") != p_jsonfile->end()) {
		component->setWinWidth(p_jsonfile->operator[]("width"));
	}

	if (p_jsonfile->find("height") != p_jsonfile->end()) {
		component->setWinHeight(p_jsonfile->operator[]("height"));
	}

	return component;
}

std::map<std::string, kitten::K_Component* (*)(nlohmann::json* p_jsonfile)> jsoncomponentmap;
void setupComponentMap() {
	jsoncomponentmap["MoveByMouseRightClickDrag"] = &getMoveByMouseRightClickDragComponentDataFrom;
	jsoncomponentmap["ZoomByMouseWheel"] = &getZoomByMouseWheelComponentDataFrom;
	jsoncomponentmap["Camera"] = &getCameraComponentDataFrom;
}

kitten::K_Component* getRelatedComponentBy(std::string key,nlohmann::json* p_jsonfile) {
	if (jsoncomponentmap.find(key) != jsoncomponentmap.end()) {
		return jsoncomponentmap[key](p_jsonfile);
	}
	return nullptr;
}