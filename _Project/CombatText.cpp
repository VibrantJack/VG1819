#include "CombatText.h"
#include "kitten\K_GameObjectManager.h"
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

	//Delete the pooled objects
}

void CombatText::start()
{
	kitten::K_GameObjectManager* gameObjMan = kitten::K_GameObjectManager::getInstance();
	kitten::K_ComponentManager* compMan = kitten::K_ComponentManager::getInstance();

	for (int i = 0; i < m_poolSize; ++i)
	{
		kitten::K_GameObject* obj = gameObjMan->createNewGameObject();
		auto textBox = static_cast<puppy::TextBox*>(compMan->createComponent("TextBox"));
		obj->addComponent(textBox);

		m_textBoxes.push(textBox);
	}
}

void CombatText::floatText(const std::string& p_text, const glm::vec3& p_place, const float& p_time, const glm::vec3& p_color, const glm::vec2& p_scale)
{
	assert(sm_instance != nullptr);
	sm_instance->privateFloatText(p_text, p_place, p_time, p_color, p_scale);
}

void CombatText::privateFloatText(const std::string& p_text, const glm::vec3& p_place, const float& p_time, const glm::vec3& p_color, const glm::vec2& p_scale)
{

}