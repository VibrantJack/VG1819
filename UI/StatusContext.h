#pragma once

#include "kitten\K_Component.h"
#include "_Project/LerpController.h"
#include "puppy\Text\TextBox.h"
#include "UI\UIObject.h"
#include "ability\status\Status.h"
#include <unordered_set>

class StatusContext : public kitten::K_Component
{
private:
	kitten::K_GameObject* m_background = nullptr;


	std::string m_buffs = "";
	std::string m_debuffs = "";
	std::string m_shields = "";
	puppy::TextBox* m_buffsTextbox = nullptr;
	puppy::TextBox* m_debuffsTextbox = nullptr;
	puppy::TextBox* m_shieldsTextbox = nullptr;

	userinterface::UIObject* m_buffsIcon = nullptr;
	userinterface::UIObject* m_debuffsIcon = nullptr;
	userinterface::UIObject* m_shieldsIcon = nullptr;

	LerpController* m_lerpController = nullptr;

	glm::vec3 m_enabledPos;
	glm::vec3 m_disabledPos;
	bool m_displayed = false;
	bool m_visible = false;

public:
	StatusContext();
	~StatusContext();

	virtual void start() override;

	virtual void onEnabled() override;
	virtual void onDisabled() override;

	void updateContext(const std::unordered_set<ability::Status*>& p_statusList);

	void lerpContext();
};