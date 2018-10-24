#pragma once

#include <string>
#include <map>

#include "Material.h"

namespace puppy
{
	class P_Instance;

	class MaterialManager
	{
		friend class P_Instance;
	private:
		//Singleton related
		MaterialManager();
		~MaterialManager();
		static MaterialManager* sm_instance;
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new MaterialManager(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };


		//Members
		std::map<const std::string, Material*> m_createdMaterials;
	public:
		
		static MaterialManager * getInstance() { return sm_instance; };

		void loadMaterials(const std::string& p_XMLToLoad);
		Material* getMaterial(const std::string& p_name) const;
	};
}