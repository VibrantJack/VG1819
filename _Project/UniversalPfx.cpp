#include "UniversalPfx.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_ComponentManager.h"
#include <iostream>

UniversalPfx* UniversalPfx::sm_instance = nullptr;

UniversalPfx::UniversalPfx(const std::list<std::tuple<std::string, std::string, int>>& p_effects, bool p_isDebug, char p_refreshKey) :
	m_isDebug(p_isDebug), m_debugRefreshKey(p_refreshKey), m_inputMan(nullptr)
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
			//Make the pfx
			kitten::K_GameObject* gameObject = kitten::K_GameObjectManager::getInstance()->createNewGameObject(effectPath);
			gameObject->setEnabled(false);

			//Insert effect into map
			m_effects[effectName].push(gameObject);

			m_particleSystems.push_back(gameObject->getComponent<kitten::K_ParticleSystem>());
		}
	}
}

UniversalPfx::~UniversalPfx()
{
	auto gameObjMan = kitten::K_GameObjectManager::getInstance();

	// Destroy effects
	/*auto end = m_effects.cend();
	for (auto it = m_effects.cbegin(); it != end; ++it)
	{
		auto queue = (*it).second;
		while (!queue.empty())
		{
			auto& gameObj = queue.front()->getGameObject();
			queue.pop();
			gameObjMan->destroyGameObject(&gameObj);
		}
	}*/

	sm_instance = nullptr;
}

void UniversalPfx::start()
{
	if (m_isDebug)
	{
		m_inputMan = input::InputManager::getInstance();
		assert(m_inputMan != nullptr);
	}
	else
	{
		setEnabled(false);
	}
}

void UniversalPfx::update()
{
	if (m_inputMan->keyDown(m_debugRefreshKey) && !m_inputMan->keyDownLast(m_debugRefreshKey))
	{
		auto end = m_particleSystems.cend();
		for (auto it = m_particleSystems.cbegin(); it != end; ++it)
		{
			(*it)->refreshXML();
		}
	}
}

void UniversalPfx::playEffect(const std::string& p_effectName, const glm::vec3& p_where)
{
	auto found = m_effects.find(p_effectName);
	if (found == m_effects.end())
	{
		std::cout << "Could not find " + p_effectName + ". Playing default pfx\n";
		found = m_effects.find("Default");
	}

	auto particleSystem = (*found).second.front();
	(*found).second.pop();

	particleSystem->getTransform().place(p_where.x, p_where.y, p_where.z);

	(*found).second.push(particleSystem);

	particleSystem->setEnabled(true);
}

void UniversalPfx::addEffectToGroup(const std::string& p_effectName, const glm::vec3& p_position)
{
	m_groupedEffects.insert(std::make_pair(p_effectName, p_position));
}

void UniversalPfx::playGroupedEffects()
{
	auto end = m_groupedEffects.end();
	for (auto it = m_groupedEffects.begin(); it != m_groupedEffects.end(); it++ )
	{
		playEffect(it->first, it->second);
	}
	m_groupedEffects.clear();
}

