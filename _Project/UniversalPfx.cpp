#include "UniversalPfx.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_ComponentManager.h"

UniversalPfx* UniversalPfx::sm_instance = nullptr;

UniversalPfx::UniversalPfx(const std::list<std::pair<std::string, std::string>>& p_effects)
{
	assert(sm_instance == nullptr);
	sm_instance = this;

	auto end = p_effects.cend();
	for (auto it = p_effects.cbegin(); it != end; ++it)
	{
		auto pair = (*it);
		auto effectName = pair.first;
		auto effectPath = pair.second;

		//Make a gamobject with a particle system component for the effect
		kitten::K_GameObject* gameObject = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		kitten::K_ParticleSystem* particleSystem = static_cast<kitten::K_ParticleSystem*>(kitten::K_ComponentManager::getInstance()->createComponent("K_ParticleSystem"));
		gameObject->addComponent(particleSystem);

		//particleSystem->setEnabled(false);
		particleSystem->setEffectXML(effectPath.c_str());

		//Insert effect into map
		m_effects.insert(std::make_pair(effectName, particleSystem));
	}
}

UniversalPfx::~UniversalPfx()
{
	auto gameObjMan = kitten::K_GameObjectManager::getInstance();

	// Destroy effects
	auto end = m_effects.cend();
	for (auto it = m_effects.cbegin(); it != end; ++it)
	{
		auto& gameObj = (*it).second->getGameObject();
		gameObjMan->destroyGameObject(&gameObj);
	}

	sm_instance = nullptr;
}

void UniversalPfx::playEffect(const std::string& p_effectName, const glm::vec3& p_where)
{
	auto found = m_effects.find(p_effectName);
	assert(found != m_effects.end());

	auto particleSystem = (*found).second;

	particleSystem->getTransform().place(p_where.x, p_where.y, p_where.z);
	//particleSystem->setEnabled(true);
	particleSystem->play();

	// @TODO: Disable particle system after it is done playing / bursting
}
