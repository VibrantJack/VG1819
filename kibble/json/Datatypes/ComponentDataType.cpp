#include "ComponentDataType.hpp"
#include <string>

#define jsonHas(str) p_jsonFile->find(str) != p_jsonFile->end()
#define lookUp(str) p_jsonFile->operator[](str)
#define setVar(varName,jsonName) varName = p_jsonFile->operator[](jsonName)
#define setOptionalVar(varName,jsonName) if(jsonHas(jsonName)) setVar(varName,jsonName)
#define setOptionalVarWithDefault(varName,jsonName,defaultVal) if(jsonHas(jsonName)) setVar(varName,jsonName); else varName = defaultVal

#include "_Project/MoveByMouseRightClickDrag.h"
kitten::K_Component* getMoveByMouseRightClickDrag(nlohmann::json* p_jsonFile) {
	float speed;

	setOptionalVarWithDefault(speed, "speed", 0.005f);

	return new MoveByMouseRightClickDrag(speed);
}

#include "_Project/ZoomByMouseWheel.h"
kitten::K_Component* getZoomByMouseWheel(nlohmann::json* p_jsonFile) {
	float speed;
	int minFOV, maxFOV;

	setOptionalVarWithDefault(speed, "speed", 1.0f);
	setOptionalVarWithDefault(minFOV, "minfov", 1);
	setOptionalVarWithDefault(maxFOV, "maxfov", 90);

	return new ZoomByMouseWheel(speed, minFOV, maxFOV); 
}

#include "kitten/Camera.h"
kitten::K_Component* getCamera(nlohmann::json* p_jsonFile) {
	kitten::Camera* component = new kitten::Camera();
	if (p_jsonFile->find("fov") != p_jsonFile->end()) {
		component->setFOV(p_jsonFile->operator[]("fov"));
	}

	if (p_jsonFile->find("near") != p_jsonFile->end()) {
		component->setNearClip(p_jsonFile->operator[]("near"));
	}

	if (p_jsonFile->find("far") != p_jsonFile->end()) {
		component->setFarClip(p_jsonFile->operator[]("far"));
	}

	if (p_jsonFile->find("width") != p_jsonFile->end()) {
		component->setWinWidth(p_jsonFile->operator[]("width"));
	}

	if (p_jsonFile->find("height") != p_jsonFile->end()) {
		component->setWinHeight(p_jsonFile->operator[]("height"));
	}

	return component;
}

#include "kitten/CubeRenderable.h"
kitten::K_Component* getCubeRenderable(nlohmann::json* p_jsonFile) {
	std::string texturefilename;

	setOptionalVarWithDefault(texturefilename, "texture", "textures/tiles/MISSING.tga");

	return new kitten::CubeRenderable(texturefilename.c_str());
}

#include "kitten/QuadRenderable.h"
kitten::K_Component* getQuadRenderable(nlohmann::json* p_jsonFile) {
	std::string texturefilename;
	bool isStatic;

	setOptionalVarWithDefault(texturefilename, "texture", "textures/tiles/MISSING.tga");
	setOptionalVarWithDefault(isStatic, "static", false);

	return new kitten::QuadRenderable(texturefilename.c_str(), isStatic);
}

#include "gameworld/GrassLandInfoComponent.h"
kitten::K_Component* getGrassLandInfo(nlohmann::json* p_jsonFile) {
	return new gameworld::GrasslandInfoComponent();
}

#include "_Project/DebugPrintOnce.h"
kitten::K_Component* getDebugPrintOnce(nlohmann::json* p_jsonFile){
	std::string message;

	setOptionalVarWithDefault(message, "message", "Default Message");

	return new DebugPrintOnce(message);
}

#include "board/clickable/PrintWhenClicked.h"
kitten::K_Component* getPrintWhenClicked(nlohmann::json* p_jsonFile) {
	std::string message;

	setOptionalVarWithDefault(message, "message", "Default Message");

	return new PrintWhenClicked(message);
}

#include "kitten\mouse picking\ClickableBox.h"
kitten::K_Component* getClickableBox(nlohmann::json* p_jsonFile) {
	glm::vec3 minPoint, maxPoint;

	if (jsonHas("minpoint")) {
		minPoint = glm::vec3(lookUp("minpoint")[0], lookUp("minpoint")[1], lookUp("minpoint")[2]);
	}

	if (jsonHas("maxpoint")) {
		minPoint = glm::vec3(lookUp("maxpoint")[0], lookUp("maxpoint")[1], lookUp("maxpoint")[2]);
	}

	return new kitten::ClickableBox(minPoint, maxPoint);
}

#include "_Project\DestroyOnClick.h"
kitten::K_Component* getDestroyOnClick(nlohmann::json* p_jsonFile){
	return new DestroyOnClick();
}


#include "board/component/BoardCreator.h"
kitten::K_Component* getBoardCreator(nlohmann::json* p_jsonFile){
	BoardCreator* component = new BoardCreator();
	int x,z;
	setOptionalVarWithDefault(x, "rows", 15);
	setOptionalVarWithDefault(z, "columns", 15);
	component->setDimension(x, z);
	return component;
}

#include "kitten\audio\AudioSource.h"
kitten::K_Component* getAudioSource(nlohmann::json* p_jsonFile) {

	std::string pathToClip;
	bool is3D, enableEffects, causesDuck, getsDucked;

	setVar(pathToClip, "clippath");
	setOptionalVar(is3D, "is3d");
	setOptionalVar(enableEffects, "enableeffects");
	setOptionalVarWithDefault(causesDuck, "causesduck", false);
	setOptionalVarWithDefault(getsDucked, "getsducked", false);

	kitten::AudioSource* toReturn = new kitten::AudioSource(pathToClip, is3D, enableEffects, causesDuck, getsDucked);

	if (is3D) {
		if (jsonHas("mindistance")) {
			toReturn->setMinDistance(lookUp("mindistance"));
		}

		if (jsonHas("maxdistance")) {
			toReturn->setMaxDistance(lookUp("maxdistance"));
		}
	}

	if (jsonHas("loop")) {
		toReturn->setLooped(lookUp("loop"));
	}

	if (jsonHas("volume")) {
		toReturn->setVolume(lookUp("volume"));
	}

	if (jsonHas("playprogress")) {
		toReturn->setPlayProgress(lookUp("playprogress"));
	}

	if (enableEffects) {
		//Effects parsing here

#define innerJsonHas(str) innerJson.find(str) != innerJson.end()
#define setInnerVar(varName,jsonName) if(innerJsonHas(jsonName)) varName = innerJson.operator[](jsonName)

		auto sfx = toReturn->getSFXControl();

		if (p_jsonFile->find("choruseffect") != p_jsonFile->end()) {
			irrklang::ik_f32 wetDryMix = 50, depth = 10, feedback = 25, frequency = 1.1;
			bool sinusWaveForm = true;
			irrklang::ik_f32 delay = 16, phase = 90;
			
			auto innerJson = p_jsonFile->operator[]("choruseffect");

			setInnerVar(wetDryMix, "wetdrymix");
			setInnerVar(depth, "depth");
			setInnerVar(feedback, "feedback");
			setInnerVar(frequency, "frequency");
			setInnerVar(sinusWaveForm, "sinuswaveform");
			setInnerVar(delay, "delay");
			setInnerVar(phase, "phase");

			sfx->setChorusEffect(wetDryMix, depth, feedback, frequency, sinusWaveForm, delay, phase);
		}

		if (p_jsonFile->find("compressoreffect") != p_jsonFile->end()) {
			irrklang::ik_f32 gain = 0, attack = 10, release = 200, threshold = -20,
				ratio = 3, preDelay = 4;

			auto innerJson = p_jsonFile->operator[]("compressoreffect");

			setInnerVar(gain, "gain");
			setInnerVar(attack, "attack");
			setInnerVar(release, "release");
			setInnerVar(threshold, "threshold");
			setInnerVar(ratio, "ratio");
			setInnerVar(preDelay, "predelay");

			sfx->setCompressorEffect(gain, attack, release, threshold, ratio, preDelay);
		}

		if (p_jsonFile->find("distortioneffect") != p_jsonFile->end()) {
			irrklang::ik_f32 gain = -18, edge = 15, postEQCenterFrequency = 2400,
				postEQBandwidth = 2400, preLowpassCutoff = 8000;

			auto innerJson = p_jsonFile->operator[]("distortioneffect");

			setInnerVar(gain, "gain");
			setInnerVar(edge, "edge");
			setInnerVar(postEQCenterFrequency, "posteqcenterfrequency");
			setInnerVar(postEQBandwidth, "posteqbandwidth");
			setInnerVar(preLowpassCutoff, "prelowpasscutoff");

			sfx->setDistortionEffect(gain, edge, postEQCenterFrequency, postEQBandwidth, preLowpassCutoff);
		}

		if (p_jsonFile->find("echoeffect") != p_jsonFile->end()) {
			irrklang::ik_f32 wetDryMix = 50, feedback = 50,
				leftDelay = 500, rightDelay = 500, panDelay = 0;

			auto innerJson = p_jsonFile->operator[]("echoeffect");

			setInnerVar(wetDryMix, "wetdrymix");
			setInnerVar(feedback, "feedback");
			setInnerVar(leftDelay, "leftdelay");
			setInnerVar(rightDelay, "rightdelay");
			setInnerVar(panDelay, "pandelay");

			sfx->setEchoEffect(wetDryMix, feedback, leftDelay, rightDelay, panDelay);
		}

		if (p_jsonFile->find("flangereffect") != p_jsonFile->end()) {
			irrklang::ik_f32 wetDryMix = 50, depth = 100,
				feedback = -50, frequency = 0.25f, delay = 2;
			irrklang::ik_s32 phase = 0;
			bool triangleWaveForm = true;

			auto innerJson = p_jsonFile->operator[]("flangereffect");

			setInnerVar(wetDryMix, "wetdrymix");
			setInnerVar(depth, "depth");
			setInnerVar(feedback, "feedback");
			setInnerVar(frequency, "frequency");
			setInnerVar(delay, "delay");
			setInnerVar(phase, "phase");
			setInnerVar(triangleWaveForm, "trianglewaveform");

			sfx->setFlangerEffect(wetDryMix, depth, feedback, frequency, triangleWaveForm, delay, phase);
		}

		if (p_jsonFile->find("gargleeffect") != p_jsonFile->end()) {
			irrklang::ik_s32 rateHz = 20;
			bool sinusWaveForm = true;

			auto innerJson = p_jsonFile->operator[]("gargleffect");

			setInnerVar(rateHz, "ratehz");
			setInnerVar(sinusWaveForm, "sinuswaveform");

			sfx->setGargleEffect(rateHz, sinusWaveForm);
		}

		if (p_jsonFile->find("3dreverbeffect") != p_jsonFile->end()) {
			irrklang::ik_s32 room = -1000, roomHF = -100,
				reflections = -2602, reverb = 200;
			irrklang::ik_f32 roomRolloffFactor = 0, decayTime = 1.49f, decayHFRatio = 0.83f,
				reflectionsDelay = 0.007f, reverbDelay = 0.011f, diffusion = 100,
				density = 100, hfReference = 5000;

			auto innerJson = p_jsonFile->operator[]("3dreverbeffect");

			setInnerVar(room, "room");
			setInnerVar(roomHF, "roomHF");
			setInnerVar(reflections, "reflections");
			setInnerVar(reverb, "reverb");
			setInnerVar(roomRolloffFactor, "roomrollofffactor");
			setInnerVar(decayTime, "decaytime");
			setInnerVar(decayHFRatio, "decayhfratio");
			setInnerVar(reflectionsDelay, "reflectionsdelay");
			setInnerVar(reverbDelay, "reverbdelay");
			setInnerVar(diffusion, "diffusion");
			setInnerVar(density, "density");
			setInnerVar(hfReference, "hfReference");

			sfx->set3DReverbEffect(room, roomHF, roomRolloffFactor, decayTime, decayHFRatio, reflections, reflectionsDelay, reverb, reverbDelay, diffusion, density, hfReference);
		}

		if (p_jsonFile->find("parameqeffect") != p_jsonFile->end()) {
			irrklang::ik_f32 center = 8000, bandwidth = 12,
				gain = 0;

			auto innerJson = p_jsonFile->operator[]("parameqeffect");

			setInnerVar(center, "center");
			setInnerVar(bandwidth, "bandwidth");
			setInnerVar(gain, "gain");

			sfx->setParamEqEffect(center, bandwidth, gain);
		}

		if (p_jsonFile->find("wavesreverbeffect") != p_jsonFile->end()) {
			irrklang::ik_f32 gain = 0, reverbMix = 0,
				reverbTime = 1000, highFreqRTRatio = 0.001f;

			auto innerJson = p_jsonFile->operator[]("wavesreverbeffect");

			setInnerVar(gain, "gain");
			setInnerVar(reverbMix, "reverbmix");
			setInnerVar(reverbTime, "reverbtime");
			setInnerVar(highFreqRTRatio, "highfreqrtratio");

			sfx->setWavesReverbEffect(gain, reverbMix, reverbTime, highFreqRTRatio);
		}
	}

	return toReturn;
}

#include "kitten\audio\AudioListener.h"
kitten::K_Component* getAudioListener(nlohmann::json* p_jsonFile) {
	return new kitten::AudioListener();
}

#include "_Project\PlaySoundOnKeyPress.h"
kitten::K_Component* getPlaySoundOnKeyPress(nlohmann::json* p_jsonFile) {
	char key;

	if (jsonHas("key")) {
		std::string strKey = lookUp("key");
		key = strKey[0];
	}

	return new PlaySoundOnKeyPress(key);
}

#include "_Project\PlaySoundOnStart.h"
kitten::K_Component* getPlaySoundOnStart(nlohmann::json* p_jsonFile) {
	return new PlaySoundOnStart();
}

#include "_Project\ToggleSoundOnKeyPress.h"
kitten::K_Component* getToggleSoundOnStart(nlohmann::json* p_jsonFile) {
	char key;

	if (jsonHas("key")) {
		std::string strKey = lookUp("key");
		key = strKey[0];
	}

	return new ToggleSoundOnKeyPress(key);
}

#include "_Project\VolumeAdjustOnKeysPressed.h"
kitten::K_Component* getVolumeAdjustOnKeysPressed(nlohmann::json* p_jsonFile) {
	char increaseKey, decreaseKey;
	float changeAmount;

	if (jsonHas("increasekey")) {
		std::string strKey = lookUp("increasekey");
		increaseKey = strKey[0];
	}

	if (jsonHas("decreasekey")) {
		std::string strKey = lookUp("decreasekey");
		decreaseKey = strKey[0];
	}

	setOptionalVar(changeAmount, "changeamount");

	return new VolumeAdjustOnKeysPressed(increaseKey,decreaseKey,changeAmount);
}

#include "userinterface/UIFrame.h"
kitten::K_Component* getUIFrame(nlohmann::json* p_jsonFile) {
	std::string texture;

	setOptionalVarWithDefault(texture, "texture", "textures/ui/blankFrame.tga");

	return new userinterface::UIFrame(texture.c_str());
}

#include "unit/unitComponent/UnitMove.h"
kitten::K_Component* getUnitMove(nlohmann::json* p_jsonFile) {
	return new unit::UnitMove();
}

#include "unit/unitComponent/UnitClickable.h"
kitten::K_Component* getUnitClickable(nlohmann::json* p_jsonFile) {
	return new unit::UnitClickable();
}

#include "board/clickable/ManipulateTileOnClick.h"
kitten::K_Component* getManipulateTileOnClick(nlohmann::json* p_jsonFile) {
	return new ManipulateTileOnClick();
}

#include "_Project/UseAbilityWhenClicked.h"
kitten::K_Component* getUseAbilityWhenClicked(nlohmann::json* p_jsonFile) {
	return new UseAbilityWhenClicked();
}

#include "board/clickable/SendSelfOnClick.h"
kitten::K_Component* getSendSelfOnClick(nlohmann::json* p_jsonFile) {
	return new SendSelfOnClick();
}

#include "_Project/FPSCalc.h"
kitten::K_Component* getFPSCalc(nlohmann::json* p_jsonFile) {
	return new FPSCalc();
}

#include "unit/InitiativeTracker/TrackerBlock.h"
kitten::K_Component* getTrackerBlock(nlohmann::json* p_jsonFile) {
	return new unit::TrackerBlock();
}

#include "unit/InitiativeTracker/TrackerBlockClickable.h"
kitten::K_Component* getTrackerBlockClickable(nlohmann::json* p_jsonFile) {
	return new unit::TrackerBlockClickable();
}

#include "unit/InitiativeTracker/TrackerPointer.h"
kitten::K_Component* getTrackerPointer(nlohmann::json* p_jsonFile) {
	return new unit::TrackerPointer();
}

#include "unit/InitiativeTracker/PointerUI.h"
kitten::K_Component* getPointerUI(nlohmann::json* p_jsonFile) {
	return new userinterface::PointerUI();
}

#include "unit/unitComponent/UnitGraphic.h"
kitten::K_Component* getUnitGraphic(nlohmann::json* p_jsonFile) {
	std::string texture;
	unit::UnitSize size = unit::point;

	setOptionalVarWithDefault(texture, "texture", "textures/unit/Default.tga");

	if (p_jsonFile->find("unitsize") != p_jsonFile->end()) {
		std::string temp = p_jsonFile->operator[]("unitsize");
		if (temp == "point")
			size = unit::point;
		else if (temp == "cube")
			size = unit::UnitSize::cube;
	}

	return new unit::UnitGraphic(size, texture.c_str());
}

#include "puppy/Text/TextBox.h"
kitten::K_Component* getTextBox(nlohmann::json* p_jsonFile) {
	std::string font , message;
	float width, height;
	puppy::TextBox* textbox;

	setOptionalVarWithDefault(font, "font", "../fonts/common_consolas.fnt");
	setOptionalVarWithDefault(message, "message", "DEFAULT TEXT");
	setOptionalVarWithDefault(width, "width", 500);
	setOptionalVarWithDefault(height, "height", 500);

	textbox = new puppy::TextBox(puppy::FontTable::getInstance()->getFont(font.c_str()), message.c_str(), width, height);

	if (jsonHas("color")) {
		textbox->setColor(lookUp("color")[0], lookUp("color")[1], lookUp("color")[2]);
	}

	if (jsonHas("alignment")) {
		std::string temp = lookUp("alignment");
		if (temp == "left")
			textbox->setAlignment(puppy::TextBox::Alignment::left);
		else if (temp == "right")
			textbox->setAlignment(puppy::TextBox::Alignment::right);
		else if (temp == "center")
			textbox->setAlignment(puppy::TextBox::Alignment::center);
	}

	return textbox;
}

#include "_Project\ToggleEnabledOnKeyPress.h"
kitten::K_Component* getToggleEnabledOnKeyPress(nlohmann::json* p_jsonFile) {
	char key;
	
	if (p_jsonFile->find("key") != p_jsonFile->end()) {
		std::string str = p_jsonFile->operator[]("key");
		key = str[0];
	}

	return new ToggleEnabledOnKeyPress(key);
}

#include "components\SelectAbility.h"
kitten::K_Component* getSelectAbility(nlohmann::json* p_jsonFile) {
	return new SelectAbility();
}

#include "components\PowerTracker.h"
kitten::K_Component* getPowerTracker(nlohmann::json* p_jsonFile) {
	return new PowerTracker();
}

#include "board/component/Highlighter.h"
kitten::K_Component* getHighlighter(nlohmann::json* p_jsonFile) {
	return new Highlighter();
}

std::map<std::string, kitten::K_Component* (*)(nlohmann::json* p_jsonFile)> jsonComponentMap;
void setupComponentMap() {
	jsonComponentMap["MoveByMouseRightClickDrag"] = &getMoveByMouseRightClickDrag;
	jsonComponentMap["ZoomByMouseWheel"] = &getZoomByMouseWheel;
	jsonComponentMap["Camera"] = &getCamera;
	jsonComponentMap["QuadRenderable"] = &getQuadRenderable;
	jsonComponentMap["CubeRenderable"] = &getCubeRenderable;
	jsonComponentMap["GrassLandInfo"] = &getGrassLandInfo;
	jsonComponentMap["DebugPrintOnce"] = &getDebugPrintOnce;
	jsonComponentMap["PrintWhenClicked"] = &getPrintWhenClicked;
	jsonComponentMap["DestroyOnClick"] = &getDestroyOnClick;
	jsonComponentMap["ClickableBox"] = &getClickableBox;
	jsonComponentMap["AudioSource"] = &getAudioSource;
	jsonComponentMap["AudioListener"] = &getAudioListener;
	jsonComponentMap["PlaySoundOnKeyPress"] = &getPlaySoundOnKeyPress;
	jsonComponentMap["PlaySoundOnStart"] = &getPlaySoundOnStart;
	jsonComponentMap["ToggleSoundOnKeyPress"] = &getToggleSoundOnStart;
	jsonComponentMap["VolumeAdjustOnKeysPressed"] = &getVolumeAdjustOnKeysPressed;
	jsonComponentMap["UIFrame"] = &getUIFrame;
	jsonComponentMap["UnitMove"] = &getUnitMove;
	jsonComponentMap["UnitClickable"] = &getUnitClickable;
	jsonComponentMap["ManipulateTileOnClick"] = &getManipulateTileOnClick;
	jsonComponentMap["UseAbilityWhenClicked"] = &getUseAbilityWhenClicked;
	jsonComponentMap["SendSelfOnClick"] = &getSendSelfOnClick;
	jsonComponentMap["FPSCalc"] = &getFPSCalc;
	jsonComponentMap["TrackerBlock"] = &getTrackerBlock;
	jsonComponentMap["TrackerBlockClickable"] = &getTrackerBlockClickable;
	jsonComponentMap["PointerUI"] = &getPointerUI;
	jsonComponentMap["UnitGraphic"] = &getUnitGraphic;
	jsonComponentMap["TextBox"] = &getTextBox;
	jsonComponentMap["ToggleEnabledOnKeyPress"] = &getToggleEnabledOnKeyPress;
	jsonComponentMap["BoardCreator"] = &getBoardCreator;
	jsonComponentMap["SelectAbility"] = &getSelectAbility;
	jsonComponentMap["PowerTracker"] = &getPowerTracker;
	jsonComponentMap["Highlighter"] = &getHighlighter;
	
}

kitten::K_Component* getRelatedComponentBy(nlohmann::json* p_jsonFile) {
	std::string key = p_jsonFile->operator[]("name");
	if (jsonComponentMap.find(key) != jsonComponentMap.end()) {
		return jsonComponentMap[key](p_jsonFile);
	}
	return nullptr;
}