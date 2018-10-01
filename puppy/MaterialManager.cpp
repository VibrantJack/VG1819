#include "MaterialManager.h"

namespace puppy
{
	MaterialManager* MaterialManager::sm_instance = nullptr;

	MaterialManager::MaterialManager()
	{

	}

	MaterialManager::~MaterialManager()
	{
		//Destroy materials
		for (auto it = m_createdMaterials.begin(); it != m_createdMaterials.end(); it = m_createdMaterials.erase(it))
		{
			delete (*it).second;
		}
	}

	void MaterialManager::loadMaterials(const std::string& p_XMLtoLoad)
	{

	}

	Material* MaterialManager::getMaterial(const std::string& p_name) const
	{
		return m_createdMaterials.at(p_name);
	}
}