#pragma once

#include <string>
#include <map>

#include "Material.h"

namespace puppy
{
	class MaterialManager
	{
	private:
		//Singleton related
		MaterialManager();
		~MaterialManager();
		static MaterialManager* sm_instance;

		//Members
		std::map<const std::string, Material*> m_createdMaterials;
	public:
		void createInstance() { assert(sm_instance == nullptr); sm_instance = new MaterialManager(); };
		void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
		MaterialManager * getInstance() const { return sm_instance; };

		void loadMaterials(const std::string& p_XMLToLoad);
		Material* getMaterial(const std::string& p_name) const;
	};
}