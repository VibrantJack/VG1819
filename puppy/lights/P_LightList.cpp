#include "P_LightList.h"

namespace puppy
{
	P_LightList* P_LightList::sm_instance = nullptr;

	P_LightList::P_LightList()
	{

	}

	P_LightList::~P_LightList()
	{

	}

	bool P_LightList::hasDirectionalLight() const
	{
		return !m_directionalLights.empty();
	}

	const std::unordered_set<const P_DirectionalLight*>& P_LightList::getDirectionalLights() const
	{
		return m_directionalLights;
	}

	bool P_LightList::hasPointLight() const
	{
		return !m_pointLights.empty();
	}

	const std::unordered_set<const P_PointLight*>& P_LightList::getPointLights() const
	{
		return m_pointLights;
	}

	void P_LightList::addDirectionalLight(const P_DirectionalLight* p_light)
	{
		m_directionalLights.insert(p_light);
	}

	void P_LightList::removeDirectionalLight(const P_DirectionalLight* p_light)
	{
		m_directionalLights.erase(p_light);
	}

	void P_LightList::addPointLight(const P_PointLight* p_light)
	{
		m_pointLights.insert(p_light);
	}

	void P_LightList::removePointLight(const P_PointLight* p_light)
	{
		m_pointLights.erase(p_light);
	}
}