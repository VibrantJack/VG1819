#include "ComponentDataType.hpp"
#include <string>

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

	return new ZoomByMouseWheel(speed, minFOV, maxFOV); 
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

#include "kitten/CubeRenderable.h"
kitten::K_Component* getCubeRenderableComponentDataFrom(nlohmann::json* p_jsonfile) {
	std::string texturefilename;

	if (p_jsonfile->find("texture") != p_jsonfile->end()) {
		texturefilename = p_jsonfile->operator[]("texture");
	}
	else {
		texturefilename = "textures/tiles/MISSING.tga";
	}

	return new kitten::CubeRenderable(texturefilename.c_str());
}

#include "kitten/QuadRenderable.h"
kitten::K_Component* getQuadRenderableComponentDataFrom(nlohmann::json* p_jsonfile) {
	std::string texturefilename = "textures/tiles/MISSING.tga";
	bool isStatic = false;

	if (p_jsonfile->find("texture") != p_jsonfile->end()) {
		texturefilename = p_jsonfile->operator[]("texture");
	}

	if (p_jsonfile->find("static") != p_jsonfile->end()) {
		isStatic = p_jsonfile->operator[]("static");
	}

	return new kitten::QuadRenderable(texturefilename.c_str(), isStatic);
}

#include "gameworld/GrassLandInfoComponent.h"
kitten::K_Component* getGrassLandInfoComponentDataFrom(nlohmann::json* p_jsonfile) {
	return new gameworld::GrasslandInfoComponent();
}

#include "_Project/DebugPrintOnce.h"
kitten::K_Component* getDebugPrintOnceComponentDataFrom(nlohmann::json* p_jsonfile){
	std::string message = "Default Message";

	if (p_jsonfile->find("message") != p_jsonfile->end()) {
		message = p_jsonfile->operator[]("message");
	}

	return new DebugPrintOnce(message);
}

#include "_Project/PrintWhenClicked.h"
kitten::K_Component* getPrintWhenClickedComponentDataFrom(nlohmann::json* p_jsonfile) {
	std::string message = "Default Message";

	if (p_jsonfile->find("message") != p_jsonfile->end()) {
		message = p_jsonfile->operator[]("message");
	}

	return new PrintWhenClicked(message);
}

#include "kitten\mouse picking\ClickableBox.h"
kitten::K_Component* getClickableBoxComponentDataFrom(nlohmann::json* p_jsonfile) {

	glm::vec3 minPoint, maxPoint;

	if (p_jsonfile->find("minpoint") != p_jsonfile->end()) {
		minPoint = glm::vec3(p_jsonfile->operator[]("minpoint")[0], p_jsonfile->operator[]("minpoint")[1], p_jsonfile->operator[]("minpoint")[2]);
	}

	if (p_jsonfile->find("maxpoint") != p_jsonfile->end()) {
		minPoint = glm::vec3(p_jsonfile->operator[]("maxpoint")[0], p_jsonfile->operator[]("maxpoint")[1], p_jsonfile->operator[]("maxpoint")[2]);
	}

	return new kitten::ClickableBox(minPoint, maxPoint);
}

#include "_Project\DestroyOnClick.h"
kitten::K_Component* getDestroyOnClickComponentDataFrom(nlohmann::json* p_jsonfile){
	return new DestroyOnClick();
}

#include "_Project\BoardCreator.h"
kitten::K_Component* getBoardCreatorComponentDataFrom(nlohmann::json* p_jsonfile){
	return new BoardCreator();
}

std::map<std::string, kitten::K_Component* (*)(nlohmann::json* p_jsonfile)> jsoncomponentmap;
void setupComponentMap() {
	jsoncomponentmap["MoveByMouseRightClickDrag"] = &getMoveByMouseRightClickDragComponentDataFrom;
	jsoncomponentmap["ZoomByMouseWheel"] = &getZoomByMouseWheelComponentDataFrom;
	jsoncomponentmap["Camera"] = &getCameraComponentDataFrom;
	jsoncomponentmap["QuadRenderable"] = &getQuadRenderableComponentDataFrom;
	jsoncomponentmap["CubeRenderable"] = &getCubeRenderableComponentDataFrom;
	jsoncomponentmap["GrassLandInfo"] = &getGrassLandInfoComponentDataFrom;
	jsoncomponentmap["DebugPrintOnce"] = &getDebugPrintOnceComponentDataFrom;
	jsoncomponentmap["PrintWhenClicked"] = &getPrintWhenClickedComponentDataFrom;
	jsoncomponentmap["DestroyOnClick"] = &getDestroyOnClickComponentDataFrom;
	jsoncomponentmap["ClickableBox"] = &getClickableBoxComponentDataFrom;
	jsoncomponentmap["BoardCreator"] = &getBoardCreatorComponentDataFrom;
}

kitten::K_Component* getRelatedComponentBy(std::string key,nlohmann::json* p_jsonfile) {
	if (jsoncomponentmap.find(key) != jsoncomponentmap.end()) {
		return jsoncomponentmap[key](p_jsonfile);
	}
	return nullptr;
}