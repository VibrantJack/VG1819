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

	const std::unordered_set<P_DirectionalLight*>& P_LightList::getDirectionalLights() const
	{
		return m_directionalLights;
	}

	void P_LightList::addDirectionalLight(P_DirectionalLight* p_light)
	{
		m_directionalLights.insert(p_light);
	}

	void P_LightList::removeDirectionalLight(P_DirectionalLight* p_light)
	{
		m_directionalLights.erase(p_light);
	}
}