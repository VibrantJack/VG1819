#include "ComponentDataType.hpp"

#include "_Project/MoveByMouseRightClickDrag.h"
kitten::K_Component* getMoveByMouseRightClickDragComponentDataFrom(nlohmann::json* p_jsonfile) {
	return new MoveByMouseRightClickDrag(0.005f); // TODO attributes
}

#include "_Project/ZoomByMouseWheel.h"
kitten::K_Component* getZoomByMouseWheelComponentDataFrom(nlohmann::json* p_jsonfile) {
	return new ZoomByMouseWheel(); // TODO attributes
}

#include "kitten/Camera.h"
kitten::K_Component* getCameraComponentDataFrom(nlohmann::json* p_jsonfile) {
	return new kitten::Camera(); // TODO attributes
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