#pragma once

#include <cassert>
#include <unordered_set>

#include "P_DirectionalLight.h"
#include "P_PointLight.h"

namespace puppy
{	
	class P_Instance;

	class P_LightList
	{
		friend class P_Instance;
	private:
		static P_LightList* sm_instance;
		P_LightList();
		~P_LightList();

		std::unordered_set<const P_DirectionalLight*> m_directionalLights;
		std::unordered_set<const P_PointLight*> m_pointLights;

		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new P_LightList(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
	public:
		static P_LightList* getInstance() { return sm_instance; };

		bool hasDirectionalLight() const;
		const std::unordered_set<const P_DirectionalLight*>& getDirectionalLights() const;

		bool hasPointLight() const;
		const std::unordered_set<const P_PointLight*>& getPointLights() const;

		void addDirectionalLight(const P_DirectionalLight* p_light);
		void removeDirectionalLight(const P_DirectionalLight* p_light);

		void addPointLight(const P_PointLight* p_light);
		void removePointLight(const P_PointLight* p_light);
	};
}