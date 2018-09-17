#include "ComponentDataType.hpp"

#include "_Project/MoveByMouseRightClickDrag.h"
kitten::K_Component* getMoveByMouseRightClickDragComponentDataFrom(nlohmann::json* jsonfile) {
	return new MoveByMouseRightClickDrag(0.005f);
}

#include "_Project/ZoomByMouseWheel.h"
kitten::K_Component* getZoomByMouseWheelComponentDataFrom(nlohmann::json* jsonfile) {
	return new ZoomByMouseWheel();
}

#include "kitten/Camera.h"
kitten::K_Component* getCameraComponentDataFrom(nlohmann::json* jsonfile) {
	return new kitten::Camera();
}

std::map<std::string, kitten::K_Component* (*)(nlohmann::json* jsonfile)> jsoncomponentmap;
void setupComponentMap() {
	jsoncomponentmap["MoveByMouseRightClickDrag"] = &getMoveByMouseRightClickDragComponentDataFrom;
	jsoncomponentmap["ZoomByMouseWheel"] = &getZoomByMouseWheelComponentDataFrom;
	jsoncomponentmap["Camera"] = &getCameraComponentDataFrom;
}

kitten::K_Component* getRelatedComponentBy(std::string key,nlohmann::json* jsonfile) {
	if (jsoncomponentmap.find(key) != jsoncomponentmap.end()) {
		return jsoncomponentmap[key](jsonfile);
	}
	return nullptr;
}