#include "P_Instance.h"

#include "kitten\K_CameraList.h"
#include "puppy\lights\P_LightList.h"

namespace puppy
{
	P_Instance* P_Instance::sm_instance = nullptr;

	P_Instance::P_Instance()
	{
		m_materialManager = MaterialManager::getInstance();
		m_renderer = Renderer::getInstance();
		m_staticRenderables = StaticRenderables::getInstance();
		m_fontTable = FontTable::getInstance();
	}

	P_Instance::~P_Instance()
	{

	}

	void P_Instance::createInstance()
	{
		MaterialManager::createInstance();
		Renderer::createInstance();
		StaticRenderables::createInstance();
		FontTable::createInstance();
		P_LightList::createInstance();

		sm_instance = new P_Instance();
	}

	void P_Instance::destroyInstance()
	{
		MaterialManager::destroyInstance();
		Renderer::destroyInstance();
		StaticRenderables::destroyInstance();
		FontTable::destroyInstance();
		ShaderManager::destroyAllShaders();
		P_LightList::destroyInstance();

		delete sm_instance;
	}

	void P_Instance::render()
	{
		kitten::Camera* cam = kitten::K_CameraList::getInstance()->getSceneCamera();

		puppy::StaticRenderables::getInstance()->render(cam);
		puppy::Renderer::getInstance()->renderAll(cam);
	}
}