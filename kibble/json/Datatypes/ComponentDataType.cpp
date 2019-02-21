#include "ComponentDataType.hpp"
#include <string>

#include "_Project/MoveByMouseRightClickDrag.h"
#include "_Project/ZoomByMouseWheel.h"
#include "kitten/Camera.h"
#include "kitten/CubeRenderable.h"
#include "kitten/QuadRenderable.h"
#include "kitten/QuadRenderableRepeat.h"
#include "gameworld/GrassLandInfoComponent.h"
#include "_Project/DebugPrintOnce.h"
#include "board/clickable/PrintWhenClicked.h"
#include "kitten\mouse picking\ClickableBox.h"
#include "_Project\DestroyOnClick.h"
#include "components/clickables/DiscardCardOnClick.h"
#include "board/component/BoardCreator.h"
#include "kitten\audio\AudioSource.h"
#include "kitten\audio\AudioListener.h"
#include "_Project\PlaySoundOnKeyPress.h"
#include "_Project\PlaySoundOnStart.h"
#include "_Project\ToggleSoundOnKeyPress.h"
#include "_Project\VolumeAdjustOnKeysPressed.h"
#include "_Project\LoadSceneOnStart.h"
#include "ui/UIFrame.h"
#include "unit/unitComponent/UnitMove.h"
#include "board/clickable/ManipulateTileOnClick.h"
#include "_Project/UseAbilityWhenClicked.h"
#include "board/clickable/SendSelfOnClick.h"
#include "_Project/FPSCalc.h"
#include "unit/InitiativeTracker/TrackerBlock.h"
#include "unit/InitiativeTracker/TrackerBlockClickable.h"
#include "unit/InitiativeTracker/TrackerPointer.h"
#include "unit/InitiativeTracker/PointerUI.h"
#include "unit/unitComponent/UnitGraphic.h"
#include "puppy/Text/TextBox.h"
#include "_Project\ToggleEnabledOnKeyPress.h"
#include "_Project\ToggleStringInputOnKeyPress.h"
#include "components\TileInfoDisplayOnKeyPress.h"
#include "_Project\StringInputDisplay.h"
#include "components\RenameDeckComponent.h"
#include "components\SelectAbility.h"
#include "components\PowerTracker.h"

#include "board/component/Highlighter.h"
kitten::K_Component* getHighlighter(nlohmann::json* p_jsonFile) {
	return new Highlighter();
}

#include "UI/HandFrame.h"
kitten::K_Component* getHandFrame(nlohmann::json& p_json) {
	std::string texture;

	SETSTROPTDEF(texture, "texture", "textures/ui/blankFrame.tga");

	return new userinterface::HandFrame(texture.c_str());
}

#include "UI/CardUIO.h"
kitten::K_Component* getCardUIO(nlohmann::json& p_json) {
	std::string texture;

	SETSTROPTDEF(texture, "texture", "textures/ui/cardBack.tga");

	userinterface::CardUIO* object = new userinterface::CardUIO(texture.c_str());
	return object;
}

#include "kitten/mouse picking/ClickableFrame.h"
kitten::K_Component* getClickableFrame(nlohmann::json& p_json) {
	kitten::ClickableFrame::PivotType type = kitten::ClickableFrame::piv_BotLeft;
	if (JSONHAS("pivot")) {
		std::string temp = LOOKUP("pivot");
		if (temp == "left")
			type = kitten::ClickableFrame::piv_Left;
		else if (temp == "right")
			type = kitten::ClickableFrame::piv_Right;
		else if (temp == "center")
			type = kitten::ClickableFrame::piv_Center;
		else if (temp == "top")
			type = kitten::ClickableFrame::piv_Top;
		else if (temp == "bottom")
			type = kitten::ClickableFrame::piv_Bot;
		else if (temp == "botleft")
			type = kitten::ClickableFrame::piv_BotLeft;
		else if (temp == "botright")
			type = kitten::ClickableFrame::piv_BotRight;
		else if (temp == "topleft")
			type = kitten::ClickableFrame::piv_TopLeft;
		else if (temp == "topright")
			type = kitten::ClickableFrame::piv_TopRight;
	}
	return new kitten::ClickableFrame(type);
}

#include "kitten/mouse picking/ClickableUI.h"
kitten::K_Component* getClickableUI(nlohmann::json& p_json) {
	bool isEnabledOnPause;
	SETOPTDEF(isEnabledOnPause, "enabledOnPause", false);
	return new kitten::ClickableUI(isEnabledOnPause);
}

#include "UI/CommanderContext.h"
kitten::K_Component* getCommanderContext(nlohmann::json& p_json) {
	return new userinterface::CommanderContext();
}

#include "board/tile/TileInfo.h"
kitten::K_Component* getTileInfo(nlohmann::json& p_json) {
	return new TileInfo();
}

#include "networking\SpawnUnitOnKeyPress.h"
kitten::K_Component* getSpawnUnitOnKeyPress(nlohmann::json& p_json) {
	return new SpawnUnitOnKeyPress();
}

#include "networking\NetworkingConsoleMenu.h"
kitten::K_Component* getNetworkingConsoleMenu(nlohmann::json& p_json) {
	return new NetworkingConsoleMenu();
}

#include "networking\ConnectToHost.h"
kitten::K_Component* getConnectToHost(nlohmann::json& p_json) {
	return new ConnectToHost();
}

#include "kitten\sprites\SpriteAnimator.h"
kitten::K_Component* getSpriteAnimator(nlohmann::json& p_json) {

	std::string characterName;

	if (p_json.find("spritename") != p_json.end()) {
		std::string name = p_json.operator[]("spritename");
		characterName = name; // I do not know why this is needed but it is.
	}

	bool randomStart;
	SETOPTDEF(randomStart, "randomstart", true);

	return new sprites::SpriteAnimator(characterName, randomStart);
}

#include "kitten\sprites\SpriteRenderable.h"
kitten::K_Component* getSpriteRenderable(nlohmann::json& p_json) {
	return new kitten::SpriteRenderable();
}

#include "components/DeckAlterationComponent.h"
kitten::K_Component* getDeckAlterationComponent(nlohmann::json& p_json) {
	return new DeckAlterationComponent();
}

#include "components/ChangeSceneOnClick.hpp"
kitten::K_Component* getChangeSceneOnClick(nlohmann::json& p_json) {

	std::string nextScene;

	SETSTR(nextScene, "scene");

	return new ChangeSceneOnClick(nextScene);
}

#include "components/SetupDeckEditOnSceneChange.h"
kitten::K_Component* getSetupDeckEditOnSceneChange(nlohmann::json& p_json) {

	std::string nextScene;

	SETSTR(nextScene, "scene");

	return new SetupDeckEditOnSceneChange(nextScene);
}

#include "kitten\K_ParticleSystem.h"
kitten::K_Component* getKParticleSystem(nlohmann::json& p_json) {
	
	std::string pathToXML = p_json.operator[]("effectpath");
	
	return new kitten::K_ParticleSystem(pathToXML.c_str());
}

#include "_Project\ToggleParticleSystemOnKeyPress.h"
kitten::K_Component* getToggleParticleSystemOnKeyPress(nlohmann::json& p_json) {

	std::string keyStr = p_json.operator[]("key");
	return new ToggleParticleSystemOnKeyPress(keyStr[0]);
}

#include "_Project\UniversalPfx.h"
kitten::K_Component* getUniversalPfx(nlohmann::json& p_json) {
	
	bool isDebug = p_json.operator[]("debug");
	char refreshKey = 'R';

	if (JSONHAS("refresh_key"))
	{
		std::string refreshStr = p_json.operator[]("refresh_key");
		refreshKey = refreshStr[0];
	}


	std::list<std::tuple<std::string, std::string, int>> effects;

	auto end = p_json.at("effects").end();
	for (auto it = p_json.at("effects").begin(); it != end; ++it)
	{
		std::string effectName = (*it)["name"];
		std::string effectPath = (*it)["path"];
		int numPfxToPool = (*it)["poolednumber"];

		effects.push_back(std::make_tuple(effectName, effectPath, numPfxToPool));
	}

	return new UniversalPfx(effects, isDebug, refreshKey);
}

#include "components/DecksDisplay/DisplayFramePickerOnClick.h"
kitten::K_Component* getDisplayFramePickerOnClick(nlohmann::json& p_json) {
	return new DisplayFramePickerOnClick();
}

#include "components/DecksDisplay/DisplayFrameSetChangeOnClick.h"
kitten::K_Component* getDisplayFrameSetChangeOnClick(nlohmann::json& p_json) {
	int offset;

	SETOPTDEF(offset, "offset", 0);

	return new DisplayFrameSetChangeOnClick(offset);
}

#include "components/DecksDisplayFrame.h"
kitten::K_Component* getDecksDisplayFrame(nlohmann::json& p_json) {
	int marginX;
	int marginY;

	SETOPTDEF(marginY, "marginY", 0);
	SETOPTDEF(marginX, "marginX", 0);

	return new DecksDisplayFrame(marginX, marginY);
}

#include "components/DisplayFrame/DeckUnitsDisplayFrame.h"
kitten::K_Component* getDeckUnitsDisplayFrame(nlohmann::json& p_json) {
	int marginX;
	int marginY;

	SETOPTDEF(marginY, "marginY", 0);
	SETOPTDEF(marginX, "marginX", 0);

	return new DeckUnitsDisplayFrame(marginX, marginY);
}

#include "components/DisplayFrame/CommanderDisplayFrame.h"
kitten::K_Component* getCommanderDisplayFrame(nlohmann::json& p_json) {
	int marginX;
	int marginY;

	SETOPTDEF(marginY, "marginY", 0);
	SETOPTDEF(marginX, "marginX", 0);

	return new CommanderDisplayFrame(marginX, marginY);
}

#include "components/DisplayFrame/UnitDisplayFrame.h"
kitten::K_Component* getUnitDisplayFrame(nlohmann::json& p_json) {
	int marginX;
	int marginY;

	SETOPTDEF(marginY, "marginY", 0);
	SETOPTDEF(marginX, "marginX", 0);

	return new UnitDisplayFrame(marginX, marginY);
}

#include "_Project\ClickableBoxRenderable.h"
kitten::K_Component* getClickableBoxRenderable(nlohmann::json& p_json) {
	return new ClickableBoxRenderable();
}

#include "components/DeckInitializingComponent.h"
kitten::K_Component* getDeckInitializingComponent(nlohmann::json& p_json) {
	return new DeckInitializingComponent();
}

#include "components/scene change/StartGameOnClick.h"
kitten::K_Component* getStartGameOnClick(nlohmann::json& p_json) {
	std::string targetScene;
	SETSTR(targetScene, "scene");
	return new StartGameOnClick(targetScene);
}

#include "components/DeckComponent.hpp"
kitten::K_Component* getDeckComponent(nlohmann::json& p_json) {
	return new DeckComponent();
}

#include "components/testing/gameplay-init.h"
kitten::K_Component* getGameplayInit(nlohmann::json& p_json) {
	bool testing;
	SETOPTDEF(testing, "testing", true);
	return new GameplayInit(testing);
}

#include "networking\menu\NetworkJoinButton.h"
kitten::K_Component* getNetworkJoinButton(nlohmann::json& p_json) {
	std::string regularTexture, highlightedTexture;

	SETSTROPT(regularTexture, "regularTexture");
	SETSTROPT(highlightedTexture, "highlightedTexture");

	userinterface::NetworkJoinButton* button = new userinterface::NetworkJoinButton();
	button->setRegularTexture(regularTexture);
	button->setHighlightedTexture(highlightedTexture);

	return button;
}

#include "networking\menu\NetworkHostButton.h"
kitten::K_Component* getNetworkHostButton(nlohmann::json& p_json) {
	std::string regularTexture, highlightedTexture;

	SETSTROPT(regularTexture, "regularTexture");
	SETSTROPT(highlightedTexture, "highlightedTexture");

	userinterface::NetworkHostButton* button = new userinterface::NetworkHostButton();
	button->setRegularTexture(regularTexture);
	button->setHighlightedTexture(highlightedTexture);

	return button;
}

#include "networking\menu\NetworkConnectButton.h"
kitten::K_Component* getNetworkConnectButton(nlohmann::json& p_json) {
	std::string regularTexture, highlightedTexture;

	SETSTROPT(regularTexture, "regularTexture");
	SETSTROPT(highlightedTexture, "highlightedTexture");

	userinterface::NetworkConnectButton* button = new userinterface::NetworkConnectButton();
	button->setRegularTexture(regularTexture);
	button->setHighlightedTexture(highlightedTexture);

	return button;
}

#include "UI\TriggerEventButton.h"
kitten::K_Component* getTriggerEventButton(nlohmann::json& p_json) {
	std::string regularTexture, highlightedTexture, inactiveTexture, eventType;
	int eventEnum;

	SETSTROPT(regularTexture, "regularTexture");
	SETSTROPT(highlightedTexture, "highlightedTexture");
	SETSTROPTDEF(inactiveTexture, "inactiveTexture", "textures/ui/buttons/disabled_button.tga");
	SETSTROPTDEF(eventType, "event", "NONE");

	if (eventType == "Poll_For_Localhost")
		eventEnum = kitten::Event::Poll_For_Localhost;
	else if (eventType == "Join_Direct_Address")
		eventEnum = kitten::Event::Join_Direct_Address;
	else if (eventType == "Join_Localhost")
		eventEnum = kitten::Event::Join_Localhost;
	else if (eventType == "Chat_Button_Clicked")
		eventEnum = kitten::Event::Chat_Button_Clicked;
	else if (eventType == "TextChat_Scroll_Up")
		eventEnum = kitten::Event::TextChat_Scroll_Up;
	else if (eventType == "TextChat_Scroll_Down")
		eventEnum = kitten::Event::TextChat_Scroll_Down;
	else if (eventType == "Ready_Button_Clicked")
		eventEnum = kitten::Event::Ready_Button_Clicked;
	else if (eventType == "Land_Context_Set_Enabled")
		eventEnum = kitten::Event::Land_Context_Set_Enabled;
	else
		eventEnum = -1;

	userinterface::TriggerEventButton* button = new userinterface::TriggerEventButton(
		(kitten::Event::EventType) eventEnum
	);
	button->setRegularTexture(regularTexture);
	button->setHighlightedTexture(highlightedTexture);
	button->setInactiveTexture(inactiveTexture);

	return button;
}

#include "UI\TabMenu\TabMenu.h"
kitten::K_Component* getTabMenu(nlohmann::json& p_json) {
	std::string texture;

	SETSTROPTDEF(texture, "texture", "textures/ui/blankFrame.tga");
	return new TabMenu(texture.c_str());
}

#include "ui/UIObject.h"
kitten::K_Component* getUIObject(nlohmann::json& p_json) {
	std::string texture;

	SETSTROPTDEF(texture, "texture", "textures/ui/blankFrame.tga");

	return new userinterface::UIObject(texture.c_str());
}

#include "UI\TabMenu\ReturnToMainMenuButton.h"
kitten::K_Component* getReturnToMainMenuButton(nlohmann::json& p_json) {
	std::string regularTexture, highlightedTexture;
	bool isEnabledOnPause;

	SETOPTDEF(isEnabledOnPause, "enabledOnPause", false);
	SETSTROPT(regularTexture, "regularTexture");
	SETSTROPT(highlightedTexture, "highlightedTexture");

	userinterface::ReturnToMainMenuButton* button = new userinterface::ReturnToMainMenuButton();
	button->setEnabledOnPause(isEnabledOnPause);
	button->setRegularTexture(regularTexture);
	button->setHighlightedTexture(highlightedTexture);

	return button;
}

#include "UI\ClickableButton.h"
kitten::K_Component* getClickableButton(nlohmann::json& p_json) {
	std::string regularTexture, highlightedTexture, inactiveTexture;
	bool isEnabledOnPause;
	SETOPTDEF(isEnabledOnPause, "enabledOnPause", false);
	SETSTROPT(regularTexture, "regularTexture");
	SETSTROPT(highlightedTexture, "highlightedTexture");
	SETSTROPTDEF(inactiveTexture, "inactiveTexture", "textures/ui/buttons/disabled_button.tga");


	userinterface::ClickableButton* button = new userinterface::ClickableButton();
	button->setEnabledOnPause(isEnabledOnPause);
	button->setRegularTexture(regularTexture);
	button->setHighlightedTexture(highlightedTexture);
	button->setInactiveTexture(inactiveTexture);

	return button;
}

#include "components\MainMenuBoard.h"
kitten::K_Component* getMainMenuBoard(nlohmann::json& p_json)
{
	return new MainMenuBoard();
}

#include "unit/InitiativeTracker/UnitAura.h"
kitten::K_Component* getUnitAura(nlohmann::json& p_json) {
	float p_speed, p_max, p_min;

	SETOPTDEF(p_speed, "speed",1.0f);
	SETOPTDEF(p_max, "max",1.2f);
	SETOPTDEF(p_min, "min",0.8f);

	return new unit::UnitAura(p_speed,p_max,p_min);
}

#include "unit/unitComponent/UnitSelect.h"
kitten::K_Component* getUnitSelect(nlohmann::json& p_json) {
	return new unit::UnitSelect();
}

#include "components/DrawCardOnClickUI.h"
kitten::K_Component* getDrawCardOnClickUI(nlohmann::json& p_json) {
	return new DrawCardOnClickUI();
}

#include "components/initializers/DrawCardsFromDeckWithDelay.h"
kitten::K_Component* getDrawCardsFromDeckWithDelay(nlohmann::json& p_json) {
	return new DrawCardsFromDeckWithDelay();
}

#include "components/DeckDiscardedCardHandler.h"
kitten::K_Component* getDeckDiscardedCardHandler(nlohmann::json& p_json) {
	return new DeckDiscardedCardHandler();
}

#include "kitten/sprites/SpriteGroup.h"
kitten::K_Component* getSpriteGroup(nlohmann::json& p_json) {
	std::string name;
	int n;
	SETSTROPT(name, "spritename");
	SETOPTDEF(n, "number", 1);

	sprites::SpriteGroup* sg = new sprites::SpriteGroup(name, n);

	if (p_json.find("rotate") != p_json.end()) {
		sg->setRotation(glm::vec3(p_json.operator[]("rotate")[0], p_json.operator[]("rotate")[1], p_json.operator[]("rotate")[2]));
	}

	if (p_json.find("scale") != p_json.end()) {
		sg->setScale(glm::vec3(p_json.operator[]("scale")[0], p_json.operator[]("scale")[1], p_json.operator[]("scale")[2]));
	}

	if (p_json.find("translate") != p_json.end()) {
		sg->setTranslation(glm::vec3(p_json.operator[]("translate")[0], p_json.operator[]("translate")[1], p_json.operator[]("translate")[2]));
	}

	return sg;
}

#include "components/CustomCursor.h"
kitten::K_Component* getCustomCursor(nlohmann::json& p_json) {
	if (JSONHAS("offset"))
	{
		return new CustomCursor(p_json.operator[]("offset")[0], p_json.operator[]("offset")[1]);
	}
	return new CustomCursor();
}

#include "UI/UIElement.h"

#include "UI\Borders\BorderPiece.h"
kitten::K_Component* getBorderPiece(nlohmann::json& p_json)
{
	userinterface::BorderPiece::BorderPlacement placement = userinterface::BorderPiece::BorderPlacement::bp_BotLeft;
	std::string texture;
	SETSTROPTDEF(texture, "texture", "textures/ui/frames/frameAtlas.tga");

	if (JSONHAS("placement"))
	{
		std::string temp = LOOKUP("placement");
		if (temp == "left")
			placement = userinterface::BorderPiece::BorderPlacement::bp_Left;
		else if (temp == "right")
			placement = userinterface::BorderPiece::BorderPlacement::bp_Right;
		else if (temp == "top")
			placement = userinterface::BorderPiece::BorderPlacement::bp_Top;
		else if (temp == "bottom")
			placement = userinterface::BorderPiece::BorderPlacement::bp_Bot;
		else if (temp == "botleft")
			placement = userinterface::BorderPiece::BorderPlacement::bp_BotLeft;
		else if (temp == "botright")
			placement = userinterface::BorderPiece::BorderPlacement::bp_BotRight;
		else if (temp == "topleft")
			placement = userinterface::BorderPiece::BorderPlacement::bp_TopLeft;
		else if (temp == "topright")
			placement = userinterface::BorderPiece::BorderPlacement::bp_TopRight;
		else
			placement = userinterface::BorderPiece::BorderPlacement::bp_BotLeft; 
	}
	if (JSONHAS("texture"))
	{
		texture = LOOKUPSTR("texture");
	}

	userinterface::BorderPiece* piece = new userinterface::BorderPiece(placement);
	piece->setTexture(texture.c_str());
		
	return piece;
}

#include "kitten\ModelRenderable.h"
kitten::K_Component* getModelRenderable(nlohmann::json& p_json) {

	std::string modelPath = p_json.operator[]("path");

	bool flipUvs;
	SETOPTDEF(flipUvs, "flipUVs", false);

	bool isStatic;
	SETOPTDEF(isStatic, "static", true);

	return new ModelRenderable(modelPath.c_str(), flipUvs, isStatic);
}

#include "unit\unitComponent\UnitHealthBar.h"
kitten::K_Component* getUnitHealthBar(nlohmann::json& p_json) {

	glm::vec3 offset = glm::vec3(LOOKUP("offset")[0], LOOKUP("offset")[1], LOOKUP("offset")[2]);

	float lerpTime;
	SETOPTDEF(lerpTime, "lerptime", 4.0f);

	float rotation;
	SETOPTDEF(rotation, "rotation", -45);

	return new unit::UnitHealthBar(offset,lerpTime,rotation);
}

#include "_Project\LerpController.h"
kitten::K_Component* getLerpController(nlohmann::json& p_json) {

	return new LerpController();
}

#include "components/DragNDrop/SpawnUnitOnDrop.h"
kitten::K_Component* getSpawnUnitOnDrop(nlohmann::json& p_json) {
	return new SpawnUnitOnDrop();
}

#include "UI/DragNDrop.h"
kitten::K_Component* getDragNDrop(nlohmann::json& p_json) {
	bool backToOrigin;

	SETOPTDEF(backToOrigin, "backtoorigin", false);

	return new DragNDrop(backToOrigin);
}

#include "components/CameraMoveByEvent.h"
kitten::K_Component* getCameraMoveByEvent(nlohmann::json& p_json) {

	return new CameraMoveByEvent();
}

#include "components\ExitGameButton.h"
kitten::K_Component* getExitGameButton(nlohmann::json& p_json) {
	std::string regularTexture, highlightedTexture;

	SETSTROPT(regularTexture, "regularTexture");
	SETSTROPT(highlightedTexture, "highlightedTexture");

	ExitGameButton* button = new ExitGameButton();
	button->setRegularTexture(regularTexture);
	button->setHighlightedTexture(highlightedTexture);

	return button;
}

#include "components\clickables\SetCommanderOnClick.h"
kitten::K_Component* getSetCommanderOnClick(nlohmann::json& p_json) {
	std::string regularTexture, highlightedTexture, inactiveTexture;

	SETSTROPT(regularTexture, "regularTexture");
	SETSTROPT(highlightedTexture, "highlightedTexture");
	SETSTROPT(inactiveTexture, "inactiveTexture");

	SetCommanderOnClick* button = new SetCommanderOnClick();
	button->setRegularTexture(regularTexture);
	button->setHighlightedTexture(highlightedTexture);
	button->setInactiveTexture(inactiveTexture);

	return button;
}

#include "components\clickables\DiscardDeckOnClick.h"
kitten::K_Component* getDiscardDeckOnClick(nlohmann::json& p_json) {
	std::string regularTexture, highlightedTexture, inactiveTexture;

	SETSTROPT(regularTexture, "regularTexture");
	SETSTROPT(highlightedTexture, "highlightedTexture");
	SETSTROPT(inactiveTexture, "inactiveTexture");

	DiscardDeckOnClick* button = new DiscardDeckOnClick();
	button->setRegularTexture(regularTexture);
	button->setHighlightedTexture(highlightedTexture);
	button->setInactiveTexture(inactiveTexture);

	return button;
}

#include "components\clickables\SaveDeckOnClick.h"
kitten::K_Component* getSaveDeckOnClick(nlohmann::json& p_json) {
	std::string regularTexture, highlightedTexture, inactiveTexture;

	SETSTROPT(regularTexture, "regularTexture");
	SETSTROPT(highlightedTexture, "highlightedTexture");
	SETSTROPT(inactiveTexture, "inactiveTexture");

	SaveDeckOnClick* button = new SaveDeckOnClick();
	button->setRegularTexture(regularTexture);
	button->setHighlightedTexture(highlightedTexture);
	button->setInactiveTexture(inactiveTexture);

	return button;
}

#include "components\clickables\AddUnitOnClick.h"
kitten::K_Component* getAddUnitOnClick(nlohmann::json& p_json) {
	std::string regularTexture, highlightedTexture, inactiveTexture;

	SETSTROPT(regularTexture, "regularTexture");
	SETSTROPT(highlightedTexture, "highlightedTexture");
	SETSTROPT(inactiveTexture, "inactiveTexture");

	AddUnitOnClick* button = new AddUnitOnClick();
	button->setRegularTexture(regularTexture);
	button->setHighlightedTexture(highlightedTexture);
	button->setInactiveTexture(inactiveTexture);

	return button;
}

#include "components\clickables\DeleteDeckOnClick.h"
kitten::K_Component* getDeleteDeckOnClick(nlohmann::json& p_json) {
	std::string regularTexture, highlightedTexture, inactiveTexture;

	SETSTROPT(regularTexture, "regularTexture");
	SETSTROPT(highlightedTexture, "highlightedTexture");
	SETSTROPT(inactiveTexture, "inactiveTexture");

	DeleteDeckOnClick* button = new DeleteDeckOnClick();
	button->setRegularTexture(regularTexture);
	button->setHighlightedTexture(highlightedTexture);

	return button;
}

#include "components\clickables\AddNewDeckOnClick.h"
kitten::K_Component* getAddNewDeckOnClick(nlohmann::json& p_json) {
	std::string regularTexture, highlightedTexture, inactiveTexture;

	SETSTROPT(regularTexture, "regularTexture");
	SETSTROPT(highlightedTexture, "highlightedTexture");
	SETSTROPT(inactiveTexture, "inactiveTexture");

	AddNewDeckOnClick* button = new AddNewDeckOnClick();
	button->setRegularTexture(regularTexture);
	button->setHighlightedTexture(highlightedTexture);
	button->setInactiveTexture(inactiveTexture);

	return button;
}

#include "components\clickables\ChangeUnitOnClick.h"
kitten::K_Component* getChangeUnitOnClick(nlohmann::json& p_json) {
	std::string regularTexture, highlightedTexture, inactiveTexture;
	bool increments;

	SETSTROPT(regularTexture, "regularTexture");
	SETSTROPT(highlightedTexture, "highlightedTexture");
	SETSTROPT(inactiveTexture, "inactiveTexture");
	SETOPTDEF(increments, "increments", true);

	ChangeUnitOnClick* button = new ChangeUnitOnClick(increments);
	button->setRegularTexture(regularTexture);
	button->setHighlightedTexture(highlightedTexture);
	button->setInactiveTexture(inactiveTexture);

	return button;
}

#include "unit/unitComponent/unitAction/ActionSelect.h"
kitten::K_Component* getActionSelect(nlohmann::json& p_json) {
	std::pair<int, int> offset, offset2;

	if (JSONHAS("action offset"))
	{
		int x = p_json.operator[]("action offset")[0];
		int y = p_json.operator[]("action offset")[1];
		offset = std::make_pair(x, y);
	}
	if (JSONHAS("cd offset"))
	{
		int x = p_json.operator[]("cd offset")[0];
		int y = p_json.operator[]("cd offset")[1];
		offset2 = std::make_pair(x, y);
	}

	unit::ActionSelect* select = new unit::ActionSelect(offset,offset2);

	return select;
}

#include "_Project\CombatText.h"
kitten::K_Component* getCombatText(nlohmann::json& p_json) {
	int poolSize = p_json.operator[]("poolsize");
	return new CombatText(poolSize);
}

#include "puppy\Text\PivotTextBox.h"
kitten::K_Component* getPivotTextBox(nlohmann::json& p_json) {
	std::string font, message;
	userinterface::UIElement::pivotType pivot;
	float width, height;
	puppy::PivotTextBox* textbox;

	SETSTROPTDEF(font, "font", "../fonts/common_dejavu.fnt");
	SETSTROPTDEF(message, "message", "DEFAULT TEXT");
	SETOPTDEF(width, "width", 500);
	SETOPTDEF(height, "height", 500);

	puppy::TextBox::Alignment align = puppy::TextBox::Alignment::left;

	if (JSONHAS("alignment")) {
		std::string temp = LOOKUP("alignment");
		if (temp == "left") {
			align = puppy::TextBox::Alignment::left;
		}
		else if (temp == "right") {
			align = puppy::TextBox::Alignment::left;
		}
		else if (temp == "center") {
			align = puppy::TextBox::Alignment::left;
		}
	}

	if (JSONHAS("pivot")) {
		std::string temp = LOOKUP("pivot");
		if (temp == "left")
		{
			pivot = userinterface::UIElement::piv_Left;
		}
		else if (temp == "topleft")
		{
			pivot = userinterface::UIElement::piv_TopLeft;

		}
		else if (temp == "top")
		{
			pivot = userinterface::UIElement::piv_Top;

		}
		else if (temp == "topright")
		{
			pivot = userinterface::UIElement::piv_TopRight;

		}
		else if (temp == "right")
		{
			pivot = userinterface::UIElement::piv_Right;

		}
		else if (temp == "botright")
		{
			pivot = userinterface::UIElement::piv_BotRight;

		}
		else if (temp == "bot")
		{
			pivot = userinterface::UIElement::piv_Bot;

		}
		else
		{
			pivot = userinterface::UIElement::piv_BotLeft;
		}

		textbox = new puppy::PivotTextBox(puppy::FontTable::getInstance()->getFont(font.c_str()), message.c_str(), width, height, pivot, align);


	if (JSONHAS("color")) {
		textbox->setColor(LOOKUP("color")[0], LOOKUP("color")[1], LOOKUP("color")[2]);
	}

	return textbox;
	}
}

#include "_Project\DisableAfterTime.h"
kitten::K_Component* getDisableAfterTime(nlohmann::json& p_json) {
	float time = p_json.operator[]("time");
	return new DisableAfterTime(time);
}

#include "UI\MainMenu\MainMenu.h"
kitten::K_Component* getMainMenu(nlohmann::json& p_json) {
	return new MainMenu();
}

#include "components/scene change/StartNewDeckSetupWizard.h"
kitten::K_Component* getStartNewDeckSetupWizard(nlohmann::json& p_json) {
	return new StartNewDeckSetupWizard();
}

#include "components/CustomDataComponent.h"
kitten::K_Component* getCustomDataComponent(nlohmann::json& p_json) {
	CustomDataComponent* comp = new CustomDataComponent();
	
	for (nlohmann::json::iterator attribute = p_json.begin(); attribute != p_json.end(); ++attribute)
	{
		if(attribute.key() == "name")
		{ }
		else if (attribute->is_boolean())
		{
			comp->m_boolMap[attribute.key()] = *attribute;
		}
		else if (attribute->is_number_integer())
		{
			comp->m_intMap[attribute.key()] = *attribute;
		}
		else if (attribute->is_number_float())
		{
			comp->m_floatMap[attribute.key()] = *attribute;
		}
		else 
		{
			comp->m_stringMap[attribute.key()] = (*attribute).get<std::string>();
		}
	}

	return comp;
}
#include "UI\CardContext.h"
kitten::K_Component* getCardContext(nlohmann::json& p_json) {
	return new CardContext();
}

#include "UI\LandContext.h"
kitten::K_Component* getLandContext(nlohmann::json& p_json) {
	return new LandContext();
}

#include "UI\ContextMenu.h"
kitten::K_Component* getContextMenu(nlohmann::json& p_json) {
	return new userinterface::ContextMenu();
}

#include "UI\ClickableCard.h"
kitten::K_Component* getClickableCard(nlohmann::json& p_json)
{
	bool isEnabledOnPause;
	SETOPTDEF(isEnabledOnPause, "enabledOnPause", false);
	return new userinterface::ClickableCard(isEnabledOnPause);
}

#include "kitten/QuadEdgeRenderable.h"
kitten::K_Component* getQuadEdgeRenderable(nlohmann::json& p_json)
{
	float side;
	SETOPTDEF(side, "side_width", 0.025f);
	return new kitten::QuadEdgeRenderable(side);
}

#include "components/PromptPopUp.h"
kitten::K_Component* getPromptPopUp(nlohmann::json& p_json)
{
	return new PromptPopUp();
}

#include "components/clickables/PromptPopUpSuccessOnClick.h"
kitten::K_Component* getPromptPopUpSuccessOnClick(nlohmann::json& p_json)
{
	return new PromptPopUpSuccessOnClick();
}

#include "components/clickables/PromptPopUpDeclineOnClick.h"
kitten::K_Component* getPromptPopUpDeclineOnClick(nlohmann::json& p_json)
{
	return new PromptPopUpDeclineOnClick();
}

#include "board/tile/TileDecoration.h"
kitten::K_Component* getTileDecoration(nlohmann::json& p_json)
{
	TileDecoration* d = new TileDecoration();

	if (JSONHAS("texture")) {
		std::vector<std::string> list;
		//assert(p_jsonfile["components"].is_array());
		for (nlohmann::json::iterator it = p_json.operator[]("texture").begin(); it != p_json.operator[]("texture").end(); ++it) {
			list.push_back(*it);
		}
		d->setTextureList(list);
	} 

	if (JSONHAS("min_scale") && JSONHAS("max_scale"))
	{
		float x1 = p_json.operator[]("min_scale")[0];
		float y1 = p_json.operator[]("min_scale")[1];
		float z1 = p_json.operator[]("min_scale")[2];
		float x2 = p_json.operator[]("max_scale")[0];
		float y2 = p_json.operator[]("max_scale")[1];
		float z2 = p_json.operator[]("max_scale")[2];
		d->setScaleRange(glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2));
	}
	if (JSONHAS("min_rotation") && JSONHAS("max_rotation"))
	{
		float x1 = p_json.operator[]("min_rotation")[0];
		float y1 = p_json.operator[]("min_rotation")[1];
		float z1 = p_json.operator[]("min_rotation")[2];
		float x2 = p_json.operator[]("max_rotation")[0];
		float y2 = p_json.operator[]("max_rotation")[1];
		float z2 = p_json.operator[]("max_rotation")[2];
		d->setRotationRange(glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2));
	}
	if (JSONHAS("min_trans") && JSONHAS("max_trans"))
	{
		float x1 = p_json.operator[]("min_trans")[0];
		float y1 = p_json.operator[]("min_trans")[1];
		float z1 = p_json.operator[]("min_trans")[2];
		float x2 = p_json.operator[]("max_trans")[0];
		float y2 = p_json.operator[]("max_trans")[1];
		float z2 = p_json.operator[]("max_trans")[2];
		d->setTransRange(glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2));
	}

	return d;
}

#include "kitten/SimpleQuadRenderable.h"
kitten::K_Component* getSimpleQuadRenderable(nlohmann::json& p_json) {
	std::string texturefilename;
	bool isStatic, upRight;

	SETSTROPTDEF(texturefilename, "texture", "");
	SETOPTDEF(isStatic, "static", false);
	SETOPTDEF(upRight, "upright", false);

	return new kitten::SimpleQuadRenderable(texturefilename.c_str(), isStatic, upRight);
}

#include "UI\CardArt.h"
kitten::K_Component* getCardArt(nlohmann::json& p_json)
{
	std::string texture;
	SETSTROPTDEF(texture, "texture", "textures/ui/blankFrame.tga");

	return new userinterface::CardArt(texture);
}

#include "_Project\ShowLoadingOnClick.h"
kitten::K_Component* getShowLoadingOnClick(nlohmann::json& p_json) {
	return new ShowLoadingOnClick();
}

#include "_Project\ProjectileManager.h"
kitten::K_Component* getProjectileManager(nlohmann::json& p_json) {
	std::string list = p_json.operator[]("list");
	return new ProjectileManager(list);
}

#include "kitten\lights\K_DirectionalLight.h"
kitten::K_Component* getDirectionalLight(nlohmann::json& p_json) {

	bool useCallbacks;
	glm::vec3 ambientColor(0.3,0.3,0.3);
	glm::vec3 directionalColor(0.3,0.3,0.3);

	SETOPTDEF(useCallbacks, "useCallbacks", false);
	
	if (JSONHAS("ambientColor"))
	{
		ambientColor = glm::vec3(LOOKUP("ambientColor")[0], LOOKUP("ambientColor")[1], LOOKUP("ambientColor")[2]);
	}

	if (JSONHAS("directionalColor"))
	{
		directionalColor = glm::vec3(LOOKUP("directionalColor")[0], LOOKUP("directionalColor")[1], LOOKUP("directionalColor")[2]);
	}

	return new kitten::K_DirectionalLight(ambientColor, directionalColor, useCallbacks);
}

#include "kitten\lights\K_PointLight.h"
kitten::K_Component* getPointLight(nlohmann::json& p_json) {

	bool useCallbacks;
	glm::vec3 ambientColor(0.3,0.3,0.3);
	glm::vec3 pointColor(0.3, 0.3, 0.3);
	glm::vec3 attenuation(0.3, 0.3, 0.3);
	float range = 1.0f;

	SETOPTDEF(useCallbacks, "useCallbacks", false);
	SETOPTDEF(range, "range", 1.0f);

	if (JSONHAS("ambientColor"))
	{
		ambientColor = glm::vec3(LOOKUP("ambientColor")[0], LOOKUP("ambientColor")[1], LOOKUP("ambientColor")[2]);
	}

	if (JSONHAS("pointColor"))
	{
		pointColor = glm::vec3(LOOKUP("pointColor")[0], LOOKUP("pointColor")[1], LOOKUP("pointColor")[2]);
	}

	if (JSONHAS("attenuation"))
	{
		attenuation = glm::vec3(LOOKUP("attenuation")[0], LOOKUP("attenuation")[1], LOOKUP("attenuation")[2]);
	}

	return new kitten::K_PointLight(pointColor, attenuation, range, useCallbacks);
}

#include "unitInteraction/CounterGetterButton.h"
kitten::K_Component* getCounterGetterButton(nlohmann::json& p_json) {
	std::string behavior;
	CounterGetterButton::ButtonBehavior b;
	SETSTROPT(behavior, "behavior");
	
	if (behavior == "plus")
		b = CounterGetterButton::plus;
	else if (behavior == "minus")
		b = CounterGetterButton::minus;
	else if (behavior == "check")
		b = CounterGetterButton::check;
	else
		b = CounterGetterButton::cancel;

	return new CounterGetterButton(b);
}

#include "unitInteraction/CounterGetterController.h"
kitten::K_Component* getCounterGetterController(nlohmann::json& p_json) {
	return new CounterGetterController();
}

#include "components/clickables/HoverOverCardBehavior.h"
kitten::K_Component* getHoverOverCardBehavior(nlohmann::json& p_json) {
	return new HoverOverCardBehavior();
}

#include "components/DeckCountTextureBind.h"
kitten::K_Component* getDeckCountTextureBind(nlohmann::json& p_json) {
	DeckCountTextureBind* cop = new DeckCountTextureBind();

	if (JSONHAS("pairs"))
	{
		for (nlohmann::json pair : LOOKUP("pairs"))
		{
			cop->addTexPair(pair[0], pair[1]);
		}
	}

	return cop;
}

#include "unit/InitiativeTracker/NewTurnMessageController.h"
kitten::K_Component* getNewTurnMessageController(nlohmann::json& p_json) {
	float time;
	SETOPTDEF(time, "time", 1.5f);
	return new unit::NewTurnMessageController(time);
}

#include "unit/unitComponent/TimerSymbol.h"
kitten::K_Component* getTimerSymbol(nlohmann::json& p_json) {
	unit::TimerSymbol* symbol = new unit::TimerSymbol();

	if (JSONHAS("textures"))
	{
		for (int i = 0; i < LOOKUP("textures").size(); i++)
		{
			symbol->addTexture(i + 1, LOOKUP("textures")[i]);
		}
	}

	return symbol;
}

#include "_Project\ProjectileParticleSystemHelper.h"
kitten::K_Component* getProjectileParticleSystemHelper(nlohmann::json& p_json) {
	std::string effectName = p_json.operator[]("effect");
	return new ProjectileParticleSystemHelper(effectName);
}

#include "networking/TextChat.h"
kitten::K_Component* getTextChat(nlohmann::json& p_json) {
	return new TextChat();
}

#include "networking/ReadyCheck.h"
kitten::K_Component* getReadyCheck(nlohmann::json& p_json) {
	//
	std::string texture;
	SETSTROPTDEF(texture, "texture", "textures/ui/blankFrame.tga");

	userinterface::UIElement::pivotType type = userinterface::UIElement::piv_BotLeft;
	if (JSONHAS("pivot")) {
		std::string temp = LOOKUP("pivot");
		if (temp == "left")
			type = userinterface::UIElement::piv_Left;
		else if (temp == "right")
			type = userinterface::UIElement::piv_Right;
		else if (temp == "center")
			type = userinterface::UIElement::piv_Center;
		else if (temp == "top")
			type = userinterface::UIElement::piv_Top;
		else if (temp == "bottom")
			type = userinterface::UIElement::piv_Bot;
		else if (temp == "botleft")
			type = userinterface::UIElement::piv_BotLeft;
		else if (temp == "botright")
			type = userinterface::UIElement::piv_BotRight;
		else if (temp == "topleft")
			type = userinterface::UIElement::piv_TopLeft;
		else if (temp == "topright")
			type = userinterface::UIElement::piv_TopRight;
		else
			type = userinterface::UIElement::piv_BotLeft;
	}

	userinterface::UIElement::textureBehaviour tb = userinterface::UIElement::tbh_Stretch;

	if (JSONHAS("texture_behaviour"))
	{
		std::string temp = LOOKUP("behaviour");
		if (temp == "repeat")
		{
			tb = userinterface::UIElement::tbh_Repeat;
		} else if (temp == "mirror_repeat")
		{
			tb = userinterface::UIElement::tbh_RepeatMirrored;
		}
	}


	if (JSONHAS("behavior"))
	{
		std::string temp = LOOKUP("behavior");
		if (temp == "repeat")
			tb = userinterface::UIElement::tbh_Repeat;
		else if (temp == "repeat_mirror")
			tb = userinterface::UIElement::tbh_RepeatMirrored;
	}

	return new ReadyCheck(texture.c_str(), type, tb);
}

#include "_Project\UniversalSounds.h"
kitten::K_Component* getUniversalSounds(nlohmann::json& p_json) {

	std::list<std::pair<std::string, std::string>> sounds;

	auto end = p_json.operator[]("sounds").cend();
	for (auto it = p_json.operator[]("sounds").cbegin(); it != end; ++it)
	{
		std::string soundName = (*it)["sound"][0];
		std::string soundPath = (*it)["sound"][1];

		sounds.push_back(std::make_pair(soundName, soundPath));
	}

	return new UniversalSounds(sounds);
}

#include "_Project\PlaySoundOnUIClick.h"
kitten::K_Component* getPlaySoundOnUIClick(nlohmann::json& p_json) {
	return new PlaySoundOnUIClick();
}

#include "_Project\FadePointLightOverTime.h"
kitten::K_Component* getFadePointLightOverTime(nlohmann::json& p_json) {
	
	float timeToFade = p_json.operator[]("time");

	glm::vec3 endingAttenuation;

	endingAttenuation = glm::vec3(LOOKUP("end_attenuation")[0], LOOKUP("end_attenuation")[1], LOOKUP("end_attenuation")[2]);

	return new FadePointLightOverTime(timeToFade, endingAttenuation);
}

#include "_Project\PlayUniversalSoundOnUIClick.h"
kitten::K_Component* getPlayUniversalSoundOnUIClick(nlohmann::json& p_json) {
	std::string soundName = p_json.operator[]("sound_name");

	return new PlayUniversalSoundOnUIClick(soundName);
}

#include "_Project\RefreshParticleSystemOnKeyPress.h"
kitten::K_Component* getRefreshParticleSystemOnKeyPress(nlohmann::json& p_json) {
	
	char key;
	std::string keyStr = p_json.operator[]("key");
	key = keyStr[0];

	return new RefreshParticleSystemOnKeyPress(key);
}

#include "_Project\PlayParticleSystemAtMouseClick.h"
kitten::K_Component* getPlayParticleSystemAtMouseClick(nlohmann::json& p_json) {
	
	glm::vec3 offset;

	if (JSONHAS("offset"))
	{
		offset = glm::vec3(LOOKUP("offset")[0], LOOKUP("offset")[1], LOOKUP("offset")[2]);
	}

	return new PlayParticleSystemAtMouseClick(offset);
}

#include "_Project\ReloadObjectOnKeyPress.h"
kitten::K_Component* getReloadObjectOnKeyPress(nlohmann::json& p_json) {
	char key;
	std::string keyStr = p_json.operator[]("key");
	key = keyStr[0];

	std::string jsonPath = p_json.operator[]("this_json_path");

	return new ReloadObjectOnKeyPress(key, jsonPath);
}

#include "_Project\PlayParticleSystemOnEnable.h"
kitten::K_Component* getPlayParticleSystemOnEnable(nlohmann::json& p_json) {
	return new PlayParticleSystemOnEnable();
}

#include "_Project\HaltParticleSystemAfterTime.h"
kitten::K_Component* getHaltParticleSystemAfterTime(nlohmann::json& p_json) {
	
	float time = p_json.operator[]("time");
	bool isStopping = p_json.operator[]("stop");

	return new HaltParticleSystemAfterTime(time, isStopping);
}

#include "UI/TurnCounterController.h"
kitten::K_Component* getTurnCounterController(nlohmann::json& p_json) {
	return new TurnCounterController();
}

std::map<std::string, kitten::K_Component* (*)(nlohmann::json& p_jsonFile)> jsonMap;
template<typename T> kitten::K_Component* getComponent(nlohmann::json& p_jsonFile) {
	return new T(p_jsonFile);
}

#define ADDTOMAP(componentClass) jsonMap[#componentClass] = &getComponent<componentClass>
#define ADDTOMAPCUSTOM(str,componentClass) jsonMap[str] = &getComponent<componentClass>
void setupComponentMap() {
	ADDTOMAP(MoveByMouseRightClickDrag);
	ADDTOMAP(ZoomByMouseWheel);
	ADDTOMAP(DebugPrintOnce);
	ADDTOMAP(PrintWhenClicked);
	ADDTOMAP(DestroyOnClick);
	ADDTOMAP(DiscardCardOnClick);
	ADDTOMAP(PlaySoundOnKeyPress);
	ADDTOMAP(PlaySoundOnStart);
	ADDTOMAP(ToggleSoundOnKeyPress);
	ADDTOMAP(BoardCreator);
	ADDTOMAP(VolumeAdjustOnKeysPressed);
	ADDTOMAP(LoadSceneOnStart);
	ADDTOMAP(ManipulateTileOnClick);
	ADDTOMAP(UseAbilityWhenClicked);
	ADDTOMAP(SendSelfOnClick);
	ADDTOMAP(FPSCalc);
	ADDTOMAP(ToggleEnabledOnKeyPress);
	ADDTOMAP(TileInfoDisplayOnKeyPress);
	ADDTOMAP(ToggleStringInputOnKeyPress);
	ADDTOMAP(StringInputDisplay);
	ADDTOMAP(RenameDeckComponent);
	ADDTOMAP(SelectAbility);
	ADDTOMAP(PowerTracker);
	ADDTOMAP(Highlighter);

	using namespace kitten;
	ADDTOMAP(Camera);
	ADDTOMAP(CubeRenderable);
	ADDTOMAP(QuadRenderable);
	ADDTOMAP(QuadRenderableRepeat);
	ADDTOMAP(ClickableBox);
	ADDTOMAP(AudioSource);
	ADDTOMAP(AudioListener);

	using namespace userinterface;
	ADDTOMAP(UIElement);
	ADDTOMAP(UIFrame);
	ADDTOMAP(PointerUI);

	using namespace unit;
	ADDTOMAP(UnitMove);
	ADDTOMAP(UIFrame);
	ADDTOMAP(TrackerBlock);
	ADDTOMAP(TrackerBlockClickable);
	ADDTOMAP(UnitGraphic);

	using namespace puppy;
	ADDTOMAP(TextBox);

	using namespace gameworld;
	ADDTOMAPCUSTOM("GrassLandInfo", GrasslandInfoComponent);

	jsonMap["HandFrame"] = &getHandFrame;
	jsonMap["CardUIO"] = &getCardUIO;
	jsonMap["ClickableFrame"] = &getClickableFrame;
	jsonMap["ClickableUI"] = &getClickableUI;
	jsonMap["TileInfo"] = &getTileInfo;
	jsonMap["SpawnUnitOnKeyPress"] = &getSpawnUnitOnKeyPress;
	jsonMap["NetworkingConsoleMenu"] = &getNetworkingConsoleMenu;
	jsonMap["ConnectToHost"] = &getConnectToHost;
	jsonMap["ChangeSceneOnClick"] = &getChangeSceneOnClick;
	jsonMap["SetupDeckEditOnSceneChange"] = &getSetupDeckEditOnSceneChange;
	jsonMap["UniversalPfx"] = &getUniversalPfx;
	jsonMap["K_ParticleSystem"] = &getKParticleSystem;
	jsonMap["ToggleParticleSystemOnKeyPress"] = &getToggleParticleSystemOnKeyPress;
	jsonMap["SpriteAnimator"] = &getSpriteAnimator;
	jsonMap["SpriteRenderable"] = &getSpriteRenderable;
	jsonMap["DisplayFrameSetChangeOnClick"] = &getDisplayFrameSetChangeOnClick;
	jsonMap["DisplayFramePickerOnClick"] = &getDisplayFramePickerOnClick;
	jsonMap["DecksDisplayFrame"] = &getDecksDisplayFrame;
	jsonMap["DeckUnitsDisplayFrame"] = &getDeckUnitsDisplayFrame;
	jsonMap["CommanderDisplayFrame"] = &getCommanderDisplayFrame;
	jsonMap["PlayParticleSystemOnEnable"] = &getPlayParticleSystemOnEnable;
	jsonMap["UnitDisplayFrame"] = &getUnitDisplayFrame;
	jsonMap["ClickableBoxRenderable"] = &getClickableBoxRenderable;
	jsonMap["DeckInitializingComponent"] = &getDeckInitializingComponent;
	jsonMap["DeckAlterationComponent"] = &getDeckAlterationComponent;
	jsonMap["StartGameOnClick"] = &getStartGameOnClick;
	jsonMap["DeckComponent"] = &getDeckComponent;
	jsonMap["GameplayInit"] = &getGameplayInit;
	jsonMap["UniversalSounds"] = &getUniversalSounds;
	jsonMap["NetworkJoinButton"] = &getNetworkJoinButton;
	jsonMap["NetworkHostButton"] = &getNetworkHostButton;	
	jsonMap["NetworkConnectButton"] = &getNetworkConnectButton;
	jsonMap["TriggerEventButton"] = &getTriggerEventButton;
	jsonMap["TabMenu"] = &getTabMenu;
	jsonMap["UIObject"] = &getUIObject;
	jsonMap["ReturnToMainMenuButton"] = &getReturnToMainMenuButton;
	jsonMap["UnitAura"] = &getUnitAura;
	jsonMap["UnitSelect"] = &getUnitSelect;
	jsonMap["SpriteGroup"] = &getSpriteGroup;
	jsonMap["ClickableButton"] = &getClickableButton;
	jsonMap["MainMenuBoard"] = &getMainMenuBoard;
	jsonMap["CustomCursor"] = &getCustomCursor;
	jsonMap["ModelRenderable"] = &getModelRenderable;
	jsonMap["UnitHealthBar"] = &getUnitHealthBar;
	jsonMap["CameraMoveByEvent"] = &getCameraMoveByEvent;
	jsonMap["LerpController"] = &getLerpController;
	jsonMap["PlaySoundOnUIClick"] = &getPlaySoundOnUIClick;
	jsonMap["PlayUniversalSoundOnUIClick"] = &getPlayUniversalSoundOnUIClick;
	jsonMap["ExitGameButton"] = &getExitGameButton;
	jsonMap["SetCommanderOnClick"] = &getSetCommanderOnClick;
	jsonMap["SaveDeckOnClick"] = &getSaveDeckOnClick;
	jsonMap["DiscardDeckOnClick"] = &getDiscardDeckOnClick;
	jsonMap["AddUnitOnClick"] = &getAddUnitOnClick;
	jsonMap["ChangeUnitOnClick"] = &getChangeUnitOnClick;
	jsonMap["DeleteDeckOnClick"] = &getDeleteDeckOnClick;
	jsonMap["AddNewDeckOnClick"] = &getAddNewDeckOnClick;
	jsonMap["CommanderContext"] = &getCommanderContext;
	jsonMap["ActionSelect"] = &getActionSelect;
	jsonMap["DragNDrop"] = &getDragNDrop;
	jsonMap["SpawnUnitOnDrop"] = &getSpawnUnitOnDrop;
	jsonMap["CombatText"] = &getCombatText;
	jsonMap["CustomDataComponent"] = &getCustomDataComponent;
	jsonMap["DisableAfterTime"] = &getDisableAfterTime;
	jsonMap["MainMenu"] = &getMainMenu;
	jsonMap["StartNewDeckSetupWizard"] = &getStartNewDeckSetupWizard;
	jsonMap["ClickableCard"] = &getClickableCard;
	jsonMap["CardContext"] = &getCardContext;
	jsonMap["LandContext"] = &getLandContext;
	jsonMap["DrawCardOnClickUI"] = &getDrawCardOnClickUI;
	jsonMap["DrawCardsFromDeckWithDelay"] = &getDrawCardsFromDeckWithDelay;
	jsonMap["DeckDiscardedCardHandler"] = &getDeckDiscardedCardHandler;
	jsonMap["QuadEdgeRenderable"] = &getQuadEdgeRenderable;
	jsonMap["TileDecoration"] = &getTileDecoration;
	jsonMap["SimpleQuadRenderable"] = &getSimpleQuadRenderable;
	jsonMap["ShowLoadingOnClick"] = &getShowLoadingOnClick;
	jsonMap["DirectionalLight"] = &getDirectionalLight;
	jsonMap["PointLight"] = &getPointLight;
	jsonMap["PivotTextBox"] = &getPivotTextBox;
	jsonMap["CardArt"] = &getCardArt;
	jsonMap["CounterGetterController"] = &getCounterGetterController;
	jsonMap["HoverOverCardBehavior"] = &getHoverOverCardBehavior;
	jsonMap["CounterGetterButton"] = &getCounterGetterButton;
	jsonMap["ContextMenu"] = &getContextMenu;
	jsonMap["NewTurnMessageController"] = &getNewTurnMessageController;
	jsonMap["PromptPopUp"] = &getPromptPopUp;
	jsonMap["PromptPopUpSuccessOnClick"] = &getPromptPopUpSuccessOnClick;
	jsonMap["PromptPopUpDeclineOnClick"] = &getPromptPopUpDeclineOnClick;
	jsonMap["TimerSymbol"] = &getTimerSymbol;
	jsonMap["ProjectileManager"] = &getProjectileManager;
	jsonMap["ProjectileParticleSystemHelper"] = &getProjectileParticleSystemHelper;
	jsonMap["FadePointLightOverTime"] = &getFadePointLightOverTime;
	jsonMap["DeckCountTextureBind"] = &getDeckCountTextureBind;
	jsonMap["TextChat"] = &getTextChat;
	jsonMap["ReadyCheck"] = &getReadyCheck;
	jsonMap["RefreshParticleSystemOnKeyPress"] = &getRefreshParticleSystemOnKeyPress;
	jsonMap["PlayParticleSystemAtMouseClick"] = &getPlayParticleSystemAtMouseClick;
	jsonMap["ReloadObjectOnKeyPress"] = &getReloadObjectOnKeyPress;
	jsonMap["HaltParticleSystemAfterTime"] = &getHaltParticleSystemAfterTime;
	jsonMap["BorderPiece"] = &getBorderPiece;
	jsonMap["TurnCounterController"] = &getTurnCounterController;
}

kitten::K_Component* getRelatedComponentBy(nlohmann::json& p_json) {
	std::string key = LOOKUPSTR("name");
	if (jsonMap.find(key) != jsonMap.end()) {
		return jsonMap[key](p_json);
	}
	return nullptr;
}
