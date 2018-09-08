#pragma once
//-----------------------------------------------------------------------------
// File:			Renderer.h
// Original Author:	Callum MacKenzie
//-----------------------------------------------------------------------------

#include "kitten\Renderable.h"
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
	public:
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new Renderer(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
		static Renderer* getInstance() { return sm_instance; };

		void addToRender(kitten::Renderable* p_toAdd);
		void removeFromRender(kitten::Renderable* p_toRemove);

		void removeAll();

		void renderAll(const glm::mat4& p_viewProj);
	};
}