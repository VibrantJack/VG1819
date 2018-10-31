#pragma once
//-----------------------------------------------------------------------------
// File:			Renderer.h
// Original Author:	Callum MacKenzie
//-----------------------------------------------------------------------------

#include "kitten\Renderable.h"
#include "kitten\UIRenderable.h"
#include "kitten\Camera.h"

#include "P_Common.h"

#include <unordered_set>

namespace puppy
{
	class P_Instance;

	class Renderer
	{
		friend class P_Instance;
		friend class kitten::Renderable;
		friend class kitten::UIRenderable;
	private:
		//Singleton related
		Renderer();
		~Renderer();
		static Renderer* sm_instance;
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new Renderer(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };

		std::unordered_set<kitten::Renderable*> m_toRender;
		std::unordered_set<kitten::UIRenderable*> m_uiToRender;


		void addToRender(kitten::Renderable* p_toAdd);
		void removeFromRender(kitten::Renderable* p_toRemove);

		void addUIToRender(kitten::UIRenderable* p_toAdd);
		void removeUIFromRender(kitten::UIRenderable* p_toRemove);

		void renderAll(kitten::Camera* p_cam);
	public:
		static Renderer* getInstance() { return sm_instance; };

		void removeAll();
	};
}