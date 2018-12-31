#pragma once

#include <cassert>
#include <unordered_set>

#include "P_DirectionalLight.h"

namespace puppy
{	
	class P_Instance;

	class P_LightList
	{
		friend class K_Instance;
	private:
		static P_LightList* sm_instance;
		P_LightList();
		~P_LightList();

		std::unordered_set<P_DirectionalLight*> m_directionalLights;

		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new P_LightList(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
	public:
		static P_LightList* getInstance() { return sm_instance; };

		bool hasDirectionalLight() const;
		const std::unordered_set<P_DirectionalLight*>& getDirectionalLights() const;

		void addDirectionalLight(P_DirectionalLight* p_light);
		void removeDirectionalLight(P_DirectionalLight* p_light);
	};
}