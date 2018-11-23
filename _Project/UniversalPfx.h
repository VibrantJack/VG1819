#pragma once

#include "kitten\K_Component.h"
#include "kitten\K_ParticleSystem.h"

#include <string>
#include <unordered_map>
#include <list>

#define UNIT_DEATH_EFFECT_NAME "UnitDeath"

class UniversalPfx : public kitten::K_Component
{
private:
	static UniversalPfx* sm_instance;

	std::unordered_map<std::string, kitten::K_ParticleSystem*> m_effects;
	
public:
						//		              name,		pathToEffect
	UniversalPfx(const std::list<std::pair<std::string, std::string>>& p_effects);
	~UniversalPfx();

	static UniversalPfx* getInstance() { assert(sm_instance != nullptr);  return sm_instance; }

	void playEffect(const std::string& p_effectName, const glm::vec3& p_position);
};