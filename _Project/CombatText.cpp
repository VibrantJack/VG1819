#include "CombatText.h"

#include "DisableAfterTime.h"
#include "LerpController.h"

#include "kitten\K_GameObjectManager.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_ComponentManager.h"

CombatText* CombatText::sm_instance = nullptr;

CombatText::CombatText(int p_poolSzie) : m_poolSize(p_poolSzie)
{
	assert(sm_instance == nullptr);
	sm_instance = this;
}

CombatText::~CombatText()
{
	assert(sm_instance == this);
	sm_instance = nullptr;

	// @TODO
	// Delete the pooled objects
	// (Same situation as UniversalPFX)
}

void CombatText::start()
{
	kitten::K_GameObjectManager* gameObjMan = kitten::K_GameObjectManager::getInstance();
	kitten::K_ComponentManager* compMan = kitten::K_ComponentManager::getInstance();

	for (int i = 0; i < m_poolSize; ++i)
	{
		kitten::K_GameObject* obj = gameObjMan->createNewGameObject("pooled_combat_text.json");
		auto textBox = obj->getComponent<puppy::TextBox>();
		assert(textBox != nullptr);

		obj->setEnabled(false);

		m_textBoxes.push(textBox);
	}
}

void CombatText::floatText(const std::string& p_text, const glm::vec3& p_place, const float& p_time, const glm::vec3& p_color, const glm::vec2& p_scale, const float& p_heightChange)
{
	assert(sm_instance != nullptr);
	sm_instance->privateFloatText(p_text, p_place, p_time, p_color, p_scale, p_heightChange);
}

void CombatText::privateFloatText(const std::string& p_text, const glm::vec3& p_place, const float& p_time, const glm::vec3& p_color, const glm::vec2& p_scale, const float& p_heightChange)
{
	auto textBox = m_textBoxes.front();
	m_textBoxes.pop();

	textBox->setText(p_text);
	textBox->setColor(p_color.x, p_color.y, p_color.z);

	textBox->getTransform().place(p_place.x, p_place.y, p_place.z);
	textBox->getTransform().scale2D(p_scale.x, p_scale.y);

	auto disabler = textBox->getGameObject().getComponent<DisableAfterTime>();
	disabler->setTime(p_time);

	auto lerpCont = textBox->getGameObject().getComponent<LerpController>();
	glm::vec3 endPos = textBox->getTransform().getTranslation();
	endPos.y += p_heightChange;
	lerpCont->positionLerp(endPos, p_time);

	textBox->getGameObject().setEnabled(true);

	m_textBoxes.push(textBox);
}