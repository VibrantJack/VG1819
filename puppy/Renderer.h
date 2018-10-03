#pragma once
//-----------------------------------------------------------------------------
// File:			Renderer.h
// Original Author:	Callum MacKenzie
//-----------------------------------------------------------------------------

#include "kitten\Renderable.h"
#include "kitten\UIRenderable.h"
#include "kitten\Camera.h"

#include "P_Common.h"

#include <vector>

namespace puppy
{
	class Renderer
	{
	private:
		//Singleton related
		Renderer();
		~Renderer();
		static Renderer* sm_instance;


		std::vector<kitten::Renderable*> m_toRender;
		std::vector<kitten::UIRenderable*> m_uiToRender;
	public:
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new Renderer(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
		static Renderer* getInstance() { return sm_instance; };

		void addToRender(kitten::Renderable* p_toAdd);
		void removeFromRender(kitten::Renderable* p_toRemove);

		void addUIToRender(kitten::UIRenderable* p_toAdd);
		void removeUIFromRender(kitten::UIRenderable* p_toRemove);

		void removeAll();

		void renderAll(kitten::Camera* p_cam);
	};
}