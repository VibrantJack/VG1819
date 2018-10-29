#pragma once
#include "MaterialManager.h"
#include "Renderer.h"
#include "StaticRenderables.h"
#include "Text\FontTable.h"
#include "ShaderManager.h"

namespace puppy
{
	class P_Instance
	{
	private:
		P_Instance();
		~P_Instance();
		static P_Instance* sm_instance;

		MaterialManager* m_materialManager;
		Renderer* m_renderer;
		StaticRenderables* m_staticRenderables;
		FontTable* m_fontTable;
	public:
		static void createInstance();
		static void destroyInstance();

		static void render();
	};
}
