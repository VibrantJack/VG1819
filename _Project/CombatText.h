#pragma once
#include "kitten\K_Component.h"
#include "puppy\Text\TextBox.h"
#include <queue>

class CombatText : public kitten::K_Component
{
private:
	static CombatText* sm_instance;

	int m_poolSize;
	std::queue<puppy::TextBox*> m_textBoxes;

	virtual void start() override;
	void privateFloatText(const std::string& p_text, const glm::vec3& p_place, 
		const float& p_time = 1.5f, const glm::vec3& p_color = glm::vec3(1, 1, 1), const glm::vec2& p_scale = glm::vec2(0.5f, 0.5f), const float& p_heightChange = 2.0f);
public:
	CombatText(int p_poolSize);
	~CombatText();

	static void floatText(const std::string& p_text, const glm::vec3& p_place, 
		const float& p_time = 1.5f, const glm::vec3& p_color = glm::vec3(1,1,1), const glm::vec2& p_scale = glm::vec2(0.5f,0.5f), const float& p_heightChange = 2.0f);

};