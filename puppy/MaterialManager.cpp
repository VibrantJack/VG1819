#include "MaterialManager.h"

namespace puppy
{
	MaterialManager* MaterialManager::sm_instance = nullptr;

	MaterialManager::MaterialManager()
	{

	}

	MaterialManager::~MaterialManager()
	{

	}

	void MaterialManager::loadMaterials(const std::string& p_XMLtoLoad)
	{

	}

	Material* MaterialManager::getMaterial(const std::string& p_name) const
	{
		return m_createdMaterials.at(p_name);
	}
}