// CardContext
//
// Displays the stats of the hovered card
// Uses TextBoxes aligned to the card_context.tga texture to display 
// the stats
// 
//
// @Ken

#pragma once
#include "kitten\K_Component.h"
#include "unit\Unit.h"
#include "puppy\Text\TextBox.h"
#include "UI\UIObject.h"
#include <vector>
#include "kitten\event_system\EventManager.h"
#include "UI\StatusContext.h"

class CardContext : public kitten::K_Component
{
private:
	puppy::TextBox* m_nameBox = nullptr;
	puppy::TextBox* m_tagsBox = nullptr;
	puppy::TextBox* m_hpBox = nullptr;
	puppy::TextBox* m_mvBox = nullptr;
	puppy::TextBox* m_initiativeBox = nullptr;
	puppy::TextBox* m_costBox = nullptr;

	puppy::TextBox* m_abilityAttributes[3];
	puppy::TextBox* m_abilityDescriptions[3];
	puppy::TextBox* m_statusList = nullptr;

	StatusContext* m_statusContext = nullptr;
	kitten::K_GameObject* m_cardTexture = nullptr;
	userinterface::UIObject* m_unitPortrait = nullptr;

	unit::Unit* m_unitData = nullptr;
	puppy::Font* m_currentNameFont = nullptr;
	puppy::Font* m_defaultNameFont = nullptr;
	puppy::Font* m_smallNameFont = nullptr;

	int m_textBoxesIndex = 0;
	int m_nonLevelStatus = 0;
	bool m_updatedByGO = false;
	// Testing
	int m_unitId = 1;

	void registerListeners();
	void removeListeners();

	void updateUnitData();
	void updateUnitAttributes();
	void updateUnitStatus();
	void setAttribTextColor(puppy::TextBox* p_textBox, const std::string& p_currAttrib, const std::string& p_baseAttrib);
	void arrangeTextBoxes();

public:
	CardContext();
	~CardContext();

	virtual void start() override;

	// For testing only, changes the unit on the hovered card on B key pressed
	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

	void setUnit(unit::Unit* p_unit);
	void setUnitListener(kitten::Event::EventType p_type, kitten::Event* p_event);
	void updateUnitAttributesListener(kitten::Event::EventType p_type, kitten::Event* p_event);
	void updateUnitStatusListener(kitten::Event::EventType p_type, kitten::Event* p_event);

	virtual void onEnabled() override;
	virtual void onDisabled() override;
	void setEnabledListener(kitten::Event::EventType p_type, kitten::Event* p_event);
};