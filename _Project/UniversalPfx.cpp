#include "UniversalPfx.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_ComponentManager.h"

UniversalPfx* UniversalPfx::sm_instance = nullptr;

UniversalPfx::UniversalPfx(const std::list<std::tuple<std::string, std::string, int>>& p_effects)
{
	assert(sm_instance == nullptr);
	sm_instance = this;

	auto end = p_effects.cend();
	for (auto it = p_effects.cbegin(); it != end; ++it)
	{
		auto tuple = (*it);
		const auto& effectName = std::get<0>(tuple);
		const auto& effectPath = std::get<1>(tuple);
		int pfxToPool = std::get<2>(tuple);

		for (int i = 0; i < pfxToPool; ++i)
		{
			//Make a gamobject with a particle system component for the effect
			kitten::K_GameObject* gameObject = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
			kitten::K_ParticleSystem* particleSystem = static_cast<kitten::K_ParticleSystem*>(kitten::K_ComponentManager::getInstance()->createComponent("K_ParticleSystem"));
			gameObject->addComponent(particleSystem);

			//particleSystem->setEnabled(false);
			particleSystem->setEffectXML(effectPath.c_str());

			//Insert effect into map
			m_effects[effectName].push(particleSystem);
		}
	}
}

UniversalPfx::~UniversalPfx()
{
	auto gameObjMan = kitten::K_GameObjectManager::getInstance();

	// Destroy effects
	auto end = m_effects.cend();
	for (auto it = m_effects.cbegin(); it != end; ++it)
	{
		auto queue = (*it).second;
		while (!queue.empty())
		{
			auto& gameObj = queue.front()->getGameObject();
			queue.pop();
			gameObjMan->destroyGameObject(&gameObj);
		}
	}

	sm_instance = nullptr;
}

void UniversalPfx::playEffect(const std::string& p_effectName, const glm::vec3& p_where)
{
	auto found = m_effects.find(p_effectName);
	assert(found != m_effects.end());

	auto particleSystem = (*found).second.front();
	(*found).second.pop();

	particleSystem->getTransform().place(p_where.x, p_where.y, p_where.z);
	//particleSystem->setEnabled(true);
	particleSystem->play();

	(*found).second.push(particleSystem);

	// @TODO: Disable particle system after it is done playing / bursting : add component ?
}
